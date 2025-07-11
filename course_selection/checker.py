import json
import sys
from pathlib import Path
from itertools import combinations

COURSE_FILE = "course.json"
SCHEDULE_FILE = "schedule.json"


def load_json(path):
    with open(path, "r", encoding="utf-8") as f:
        return json.load(f)


try:
    courses_raw = load_json(COURSE_FILE)
    schedule_raw = load_json(SCHEDULE_FILE)
except FileNotFoundError as e:
    sys.exit(f"文件缺失: {e.filename}")


class ClassInfo:
    __slots__ = ("times", "weeks")

    def __init__(self, times, weeks):
        self.times = times
        self.weeks = weeks


class CourseInfo:
    __slots__ = ("name", "credit", "prereq", "classes")

    def __init__(self):
        self.name = ""
        self.credit = 0
        self.prereq = []
        self.classes = {}


course_map = {}
for c in courses_raw:
    cid = c.get("course_id") or c.get("id")
    if not cid:
        continue
    info = CourseInfo()
    info.name = c.get("course_name") or c.get("name", "")
    info.credit = int(c.get("credit", 0))
    info.prereq = list(c.get("prerequisites", []))

    for off in c.get("offerings", []):
        cls_id = off.get("class_id") or off.get("id")
        if not cls_id:
            continue
        times = [int(x) for x in off.get("times", [0]*7)]
        weeks = int(off.get("weeks", 0))
        info.classes[cls_id] = ClassInfo(times, weeks)

    course_map[cid] = info


sel_map = {}
for e in schedule_raw:
    cid = e.get("course_id") or e.get("id")
    if not cid:
        continue
    semester = int(e.get("semester", -1))
    cls_id = e.get("class_id") or e.get("class") or ""
    sel_map[cid] = (semester, cls_id)


def wrap(cid):
    name = course_map.get(cid, CourseInfo()).name
    return f"{cid}（{name}）" if name else cid


def overlap(a: ClassInfo, b: ClassInfo) -> bool:
    if a.weeks & b.weeks == 0:
        return False
    return any(ta & tb for ta, tb in zip(a.times, b.times))


errors = []
total_credit = 0


for cid, (sem, cls) in sel_map.items():
    if sem < 0:
        continue
    if cid not in course_map:
        errors.append(f"课程 {cid} 不存在于 {COURSE_FILE}")
        continue
    if cls not in course_map[cid].classes:
        errors.append(f"课程 {wrap(cid)} 的班号 {cls} 不在 offerings 中")


for cid, (sem, _) in sel_map.items():
    if sem < 0:
        continue
    for pre in course_map[cid].prereq:
        p_sem = sel_map.get(pre, (-1, ""))[0]
        if p_sem < 0:
            errors.append(f"课程 {wrap(cid)} 缺少先修课 {wrap(pre)}")
        elif p_sem >= sem:
            errors.append(
                f"课程 {wrap(cid)} 的先修课 {wrap(pre)} "
                f"学期 {p_sem} 需早于本课学期 {sem}"
            )


sem_table = {}
for cid, (sem, cls) in sel_map.items():
    if sem < 0 or cid not in course_map:
        continue
    ci = course_map[cid].classes.get(cls)
    if not ci:
        continue
    sem_table.setdefault(sem, []).append((cid, ci))

for sem, lst in sem_table.items():
    for (cid1, c1), (cid2, c2) in combinations(lst, 2):
        if overlap(c1, c2):
            errors.append(
                f"学期 {sem} 内 {wrap(cid1)} 与 {wrap(cid2)} 时间冲突"
            )


for cid, (sem, _) in sel_map.items():
    if sem >= 0 and cid in course_map:
        total_credit += course_map[cid].credit


if errors:
    print("✘ 发现以下问题：")
    for e in errors:
        print("  -", e)
    print(f"总学分: {total_credit}")
    sys.exit(1)
else:
    print("✔ 选课方案合法")
    print(f"总学分: {total_credit}")

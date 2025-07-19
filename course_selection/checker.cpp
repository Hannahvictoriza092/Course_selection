#include "nlohmann/json.hpp"
#include <bits/stdc++.h>
using json = nlohmann::json;

struct ClassInfo
{
    std::array<int, 7> time{};
    int weeks = 0;
};
struct CourseInfo
{
    int credit = 0;
    std::string name;
    std::vector<std::string> prereq;
    std::unordered_map<std::string, ClassInfo> classes;
};
struct SelInfo
{
    int semester = -1;
    std::string class_id;
};

json read_json(const std::string& file)
{
    std::ifstream fin(file);
    if (!fin)
        throw std::runtime_error("无法打开 " + file);
    json j;
    fin >> j;
    return j;
}
static std::string extract_name(const json& c)
{
    if (c.contains("course_name"))
        return c["course_name"];
    if (c.contains("name"))
        return c["name"];
    return "";
}
static std::string
wrap(const std::string& id,
     const std::unordered_map<std::string, CourseInfo>& mp)
{
    auto it = mp.find(id);
    if (it != mp.end() && !it->second.name.empty())
        return id + "（" + it->second.name + "）";
    return id;
}
static bool overlap(const ClassInfo& a, const ClassInfo& b)
{
    if ((a.weeks & b.weeks) == 0)
        return false;
    for (int d = 0; d < 7; ++d)
        if (a.time[d] & b.time[d])
            return true;
    return false;
}

int main()
try
{

    const json jc = read_json("course.json");
    std::unordered_map<std::string, CourseInfo> courseMap;

    for (const auto& c : jc)
    {
        std::string cid;
        if (c.contains("course_id"))
            cid = c["course_id"];
        else if (c.contains("id"))
            cid = c["id"];
        else
            continue;

        CourseInfo info;
        if (c.contains("credit"))
            info.credit = c["credit"].get<int>();
        info.name = extract_name(c);

        if (c.contains("prerequisites"))
            info.prereq =
                c["prerequisites"].get<std::vector<std::string>>();

        if (c.contains("offerings"))
            for (const auto& o : c["offerings"])
            {
                std::string cls;
                if (o.contains("class_id"))
                    cls = o["class_id"];
                else if (o.contains("id"))
                    cls = o["id"];
                if (cls.empty())
                    continue;

                ClassInfo ci;
                if (o.contains("times"))
                {
                    const auto& arr = o["times"];
                    for (int d = 0; d < 7 && d < arr.size(); ++d)
                        ci.time[d] = arr[d].get<int>();
                }
                if (o.contains("weeks"))
                    ci.weeks = o["weeks"].get<int>();
                info.classes.emplace(cls, std::move(ci));
            }
        courseMap.emplace(cid, std::move(info));
    }

    const json js = read_json("schedule.json");
    std::unordered_map<std::string, SelInfo> selMap;
    for (const auto& e : js)
    {
        std::string cid;
        if (e.contains("course_id"))
            cid = e["course_id"];
        else if (e.contains("id"))
            cid = e["id"];
        else
            continue;

        SelInfo s;
        if (e.contains("semester"))
            s.semester = e["semester"];
        if (e.contains("class_id"))
            s.class_id = e["class_id"];
        else if (e.contains("class"))
            s.class_id = e["class"];
        selMap[cid] = std::move(s);
    }

    bool allOK = true;
    std::vector<std::string> errs;
    int totalCredits = 0;

    for (const auto& [cid, s] : selMap)
    {
        if (s.semester < 0)
            continue;
        auto it = courseMap.find(cid);
        if (it == courseMap.end())
        {
            errs.emplace_back("课程 " + cid +
                              " 不存在于 course.json");
            allOK = false;
            continue;
        }
        if (it->second.classes.count(s.class_id) == 0)
        {
            errs.emplace_back("课程 " + wrap(cid, courseMap) +
                              " 的班号 " + s.class_id +
                              " 不在 offerings 中");
            allOK = false;
        }
    }

    for (const auto& [cid, s] : selMap)
    {
        if (s.semester < 0)
            continue;
        const auto& course = courseMap.at(cid);
        for (const std::string& pre : course.prereq)
        {
            auto it = selMap.find(pre);
            if (it == selMap.end() || it->second.semester < 0)
            {
                errs.emplace_back("课程 " + wrap(cid, courseMap) +
                                  " 缺少先修课 " +
                                  wrap(pre, courseMap));
                allOK = false;
            }
            else if (it->second.semester >= s.semester)
            {
                errs.emplace_back(
                    "课程 " + wrap(cid, courseMap) + " 的先修课 " +
                    wrap(pre, courseMap) + " 学期 " +
                    std::to_string(it->second.semester) +
                    " 需早于本课学期 " + std::to_string(s.semester));
                allOK = false;
            }
        }
    }

    std::unordered_map<
        int, std::vector<std::pair<std::string, const ClassInfo*>>>
        semTable;

    for (const auto& [cid, s] : selMap)
    {
        if (s.semester < 0)
            continue;
        const auto& cinfo = courseMap.at(cid);
        auto itCls = cinfo.classes.find(s.class_id);
        if (itCls == cinfo.classes.end())
            continue;
        semTable[s.semester].push_back({cid, &itCls->second});
    }

    for (const auto& [sem, vec] : semTable)
    {
        for (size_t i = 0; i < vec.size(); ++i)
            for (size_t j = i + 1; j < vec.size(); ++j)
            {
                if (overlap(*vec[i].second, *vec[j].second))
                {
                    errs.emplace_back(
                        "学期 " + std::to_string(sem) + " 内 " +
                        wrap(vec[i].first, courseMap) + " 与 " +
                        wrap(vec[j].first, courseMap) + " 时间冲突");
                    allOK = false;
                }
            }
    }

    for (const auto& [cid, s] : selMap)
        if (s.semester >= 0)
        {
            auto it = courseMap.find(cid);
            if (it != courseMap.end())
                totalCredits += it->second.credit;
        }

    if (allOK)
        std::cout << "✔ 选课方案合法\n";
    else
    {
        std::cout << "✘ 发现以下问题：\n";
        for (const auto& e : errs)
            std::cout << "  - " << e << '\n';
    }
    std::cout << "总学分: " << totalCredits << '\n';
    return allOK ? 0 : 1;
}
catch (const std::exception& e)
{
    std::cerr << "运行时错误: " << e.what() << '\n';
    return 1;
}

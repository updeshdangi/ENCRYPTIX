#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
struct Item 
{
    string name;
    vector<string> attributes; 
};
struct User 
{
    string name;
    vector<string> preferredAttributes;
};
double calculateSimilarity(const Item& item, const User& user) 
{
    if (item.attributes.empty()) 
    {
        return 0.0; 
    }

    int matchCount = 0;
    for (const string& attr : item.attributes) 
    {
        if (find(user.preferredAttributes.begin(), user.preferredAttributes.end(), attr) != user.preferredAttributes.end()) 
        {
            matchCount++;
        }
    }
    return static_cast<double>(matchCount) / item.attributes.size();
}
vector<Item> recommendItems(const vector<Item>& items, const User& user) 
{
    vector<pair<double, Item>> scoredItems;

    for (const Item& item : items) 
    {
        double score = calculateSimilarity(item, user);
        scoredItems.push_back(make_pair(score, item));
    }
    sort(scoredItems.begin(), scoredItems.end(), [](const pair<double, Item>& a, const pair<double, Item>& b) 
    {
        return a.first > b.first;
    });

    vector<Item> recommendations;
    for (const auto& scoredItem : scoredItems) 
    {
        recommendations.push_back(scoredItem.second);
    }
    return recommendations;
}

int main() 
{
    vector<Item> items = 
    {
        {"Book1", {"Fantasy", "Adventure", "Magic"}},
        {"Book2", {"Science Fiction", "Space", "Technology"}},
        {"Book3", {"Fantasy", "Adventure", "Dragons"}},
        {"Book4", {"Historical", "War", "Strategy"}},
        {"Book5", {"Science Fiction", "Space", "Aliens"}}
    };
    User user = {"Alice", {"Fantasy", "Adventure"}};
    vector<Item> recommendations = recommendItems(items, user);
    cout << "Recommended items for " << user.name << ":\n";
    for (const Item& item : recommendations) 
    {
        cout << "- " << item.name << "\n";
    }
    return 0;
}
#include "SaberTest2.h"
#include <unordered_map> 

void List::Serialize(FILE* file)
{
    fwrite(&count, sizeof(int), 1, file);

    if (!count)
    {
        return;
    }

    std::unordered_map<ListNode*, int> hashMap;
    hashMap.reserve(count);
     
    auto node = head;
    int id = 0;
    while (node)
    {
        hashMap[node] = id++;
        node = node->next;
    }

    node = head;
    while (node)
    {
        int size = static_cast<int>(node->data.size());
        fwrite(&size, sizeof(int), 1, file);

        if (size)
        {
            fputs(node->data.c_str(), file);
        }
         
        int randListId = node->rand ? hashMap[node->rand]: -1;

        fwrite(&randListId, sizeof(int), 1, file);

        node = node->next;
    }
}

void List::Deserialize(FILE* file)
{
    //clear list
    auto node = head;
    while (node)
    {
        auto current = node;
        node = node->next;
        delete current;
    }

    head = nullptr;
    tail = nullptr;
    count = 0;

    fread(&count, sizeof(int), 1, file);

    if (!count)
    {
        return;
    }

    ListNode** mNode = new ListNode*[count];

    node = new ListNode();
     
    node->prev = nullptr;
    node->next = nullptr;
    node->rand = nullptr;
    head = node;
    tail = node;
    mNode[0] = node;

    for (int i = 1; i < count; i++)
    {
        node = new ListNode();
        node->next = nullptr;
        node->rand = nullptr;
        node->prev = tail;

        mNode[i] = node;
        tail->next = node;
        tail = node;
    }

    node = head;
    while (node)
    {
        int size = -1;
        fread(&size, sizeof(int), 1, file);

        if (size)
        {
            node->data.resize(static_cast<size_t>(size));
            fgets(&node->data[0], size + 1, file);
        }

        int randListId = -1;
        fread(&randListId, sizeof(int), 1, file);

        if (randListId >= 0)
        {
            node->rand = mNode[randListId];
        }

        node = node->next;
    }

    delete[] mNode;
}
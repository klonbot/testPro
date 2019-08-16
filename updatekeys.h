#ifndef UPDATEKEYS_H
#define UPDATEKEYS_H

#include"databaseitem.h"

template <typename Bd>
class UpdateKeys
{
public:
    UpdateKeys(Bd &b):bd(b) {}

    void updateKeysRightItems(Key_t rk);
    void updateKeysAncestors(Key_t rk);
private:
    Bd &bd;
};

template <typename Bd>
void UpdateKeys<Bd>::updateKeysRightItems(Key_t rk)
{
    for(int i = 0; i < bd.size(); ++i)
    {
        DataBaseItem *item = bd.atData(i);
        if(item->getLeftKey() > rk)
        {
            item->setLeftKey(item->getLeftKey() + 2);
            item->setRightKey(item->getRightKey() + 2);
        }
    }
}

template <typename Bd>
void UpdateKeys<Bd>::updateKeysAncestors(Key_t rk)
{
    for(int i = 0; i < bd.size(); ++i)
    {
        DataBaseItem *item = bd.atData(i);
        if((item->getRightKey()>=rk)&&(item->getLeftKey()<rk))
        {
            item->setRightKey(item->getRightKey() + 2);
        }
    }
}

#endif // UPDATEKEYS_H

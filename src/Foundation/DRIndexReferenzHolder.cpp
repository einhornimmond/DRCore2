#include "DRCore2/DRCore2Main.h"

#include "DRCore2/Foundation/DRIndexReferenzHolder.h"

#include <cassert>

DRIndexReferenzHolder::DRIndexReferenzHolder(unsigned int maxIndexCount)
: mReferenzCounter(nullptr), mFreePlaces(nullptr), mFreePlaceCursor(0), mMaxIndexCount(maxIndexCount)
{
    mReferenzCounter = new unsigned int[maxIndexCount];
    memset(mReferenzCounter, 0, sizeof(unsigned int)*maxIndexCount);
    mFreePlaces = new unsigned int[maxIndexCount];
    if(!mReferenzCounter || !mFreePlaces) LOG_ERROR_VOID("no memory");

    unsigned int index = maxIndexCount-1;
    //Die Zeiger in m_ppFreeObjects werden von vorne nach hinten,
    //von hinten nach vorne auf den reservierten Speicher ausgerichtet
    for(mFreePlaceCursor = 0; mFreePlaceCursor < maxIndexCount; mFreePlaceCursor++)
    {
        mFreePlaces[mFreePlaceCursor] = index--;
    }
}

DRIndexReferenzHolder::~DRIndexReferenzHolder()
{
    DR_SAVE_DELETE_ARRAY(mReferenzCounter);
    DR_SAVE_DELETE_ARRAY(mFreePlaces);
}

void DRIndexReferenzHolder::add(unsigned int index)
{
    if(index >= mMaxIndexCount) return;
    mReferenzCounter[index]++;
}

void DRIndexReferenzHolder::remove(unsigned int index)
{
    assert(mReferenzCounter[index] > 0);
    mReferenzCounter[index]--;
    if(mReferenzCounter[index] == 0)
        mFreePlaces[mFreePlaceCursor++] = index;
}

unsigned int DRIndexReferenzHolder::getFree()
{
    if(mFreePlaceCursor == 0)
    {
        LOG_ERROR("Kein Platz mehr in der Liste!", 0);
    }
    --mFreePlaceCursor;
    mReferenzCounter[mFreePlaces[mFreePlaceCursor]] = 1;
    return mFreePlaces[mFreePlaceCursor];
}
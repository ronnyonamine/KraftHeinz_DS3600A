#include <gui/containers/KhViewData.hpp>
#include <string>
#include <touchgfx/Color.hpp>

KhViewData::KhViewData()
{

}

void KhViewData::initialize()
{
    KhViewDataBase::initialize();
    khListRecordContainer1.setAsHeader();
    listLayout1.invalidate();
}

void KhViewData::scrollLeft()
{
    if (horizontalScrollIndex <= 0) return;
    horizontalScrollIndex--;
    scrollableContainer1.moveChildrenRelative(195, 0);
    scrollableContainer1.invalidate();
}

void KhViewData::scrollRight()
{
    if (horizontalScrollIndex >= 2) return;
    horizontalScrollIndex++;
    scrollableContainer1.moveChildrenRelative(-195, 0);
    scrollableContainer1.invalidate();
}

void KhViewData::scrollUp()
{
    if (rowTop > 0)
    {
        rowTop--;
        verticalScrollIndex--;
        scrollableContainer1.moveChildrenRelative(0, 30);
        scrollableContainer1.invalidate();
    }
}

void KhViewData::scrollDown()
{
    if (verticalScrollIndex < rowTop + 3)
    {
        verticalScrollIndex++;
        return;
    }
    if (verticalScrollIndex < numberOfListElements1-2)
    {
        rowTop++;
        verticalScrollIndex++;
        scrollableContainer1.moveChildrenRelative(0, -30);
        scrollableContainer1.invalidate();
    }
}

void KhViewData::handleKeyEvent(uint8_t key)
{
    if (key == KEYCODE_RIGHT)
    {
        scrollRight();
    }
    if (key == KEYCODE_LEFT)
    {
        scrollLeft();
    }
    if (key == KEYCODE_UP)
    {
        scrollUp();
        if (rowIndex > 1)
        {
            selectDataRow(rowIndex - 1);
        }
    }
    if (key == KEYCODE_DOWN)
    {
        scrollDown();
        if (rowIndex < numberOfDataRecords)
        {
            selectDataRow(rowIndex + 1);
        }
    }
}

uint8_t KhViewData::getSelectedEntry()
{
    return rowIndex;
}

void KhViewData::clearData()
{
    delete[] listElements1;
    numberOfDataRecords = 0;
    numberOfListElements1 = 1;
    listLayout1.removeAll();
}

int KhViewData::count()
{
    return numberOfListElements1;
}

void KhViewData::selectDataRow(int index)
{
    KhListRecordContainer* listLayout1Row = (KhListRecordContainer*)listLayout1.getFirstChild();
    for (int i = 1; i < numberOfListElements1; i++)
    {
        if (i == rowIndex)
        {
            listLayout1Row->deselectThis();
        }
        if (i == index)
        {
            listLayout1Row->selectThis();
        }
        listLayout1Row = (KhListRecordContainer*)listLayout1Row->getNextSibling();
    }
    rowIndex = index;
    scrollableContainer1.invalidate();
}

void KhViewData::addDataRow(DataRecord dataRecord)
{
    listElement = new KhListRecordContainer();
    listElement->setupListElements(dataRecord.date, dataRecord.time, dataRecord.learnBarcode, dataRecord.verifyBarcode, dataRecord.success, dataRecord.reason, dataRecord.initials);
    numberOfDataRecords++;
    numberOfListElements1++;
    if (numberOfDataRecords == 1)
    {
        rowIndex = 1;
        listElement->selectThis();
    }
    listLayout1.add(*listElement);
    listLayout1.invalidate();
}

void KhViewData::addHeader()
{
    listElement = new KhListRecordContainer();
    listElement->setAsHeader();
    rowIndex = 0;
    listLayout1.add(*listElement);
    numberOfDataRecords++;
    numberOfListElements1++;
    listLayout1.invalidate();
}
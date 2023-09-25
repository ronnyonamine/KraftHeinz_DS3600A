#ifndef KHVIEWDATA_HPP
#define KHVIEWDATA_HPP

#include <gui_generated/containers/KhViewDataBase.hpp>
#include <gui/containers/KHListRecordContainer.hpp>  // Manual Edit - Module Specific

class KhViewData : public KhViewDataBase
{
public:
    KhViewData();
    virtual ~KhViewData() {}

    virtual void initialize();
    void handleKeyEvent(uint8_t key);
    uint8_t getSelectedEntry();
    void clearData();
    void addDataRow(DataRecord dataRecord);
    void selectDataRow(int index);
    void scrollLeft();
    void scrollRight();
    void scrollUp();
    void scrollDown();
    int count();
    int horizontalScrollIndex = 0;
protected:
    int numberOfListElements1 = 1;
    int numberOfDataRecords = 0;
    //int horizontalScrollIndex = 0;
    int verticalScrollIndex = 0;
    int rowIndex = 0;
    int rowTop = 0;
    KhListRecordContainer* listElements1;
    KhListRecordContainer* listElement;
    void addHeader();

};

#endif // KHVIEWDATA_HPP

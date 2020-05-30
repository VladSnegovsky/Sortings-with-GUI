#include "Sort.hpp"
#include "Index.hpp"

Index* Father = NULL;
Index* last;

int nextInd = 0;
QVector<int> elementsVector;

namespace lab::ui {

void Sort::makeArray(QString newNum)
{
    if (Father == NULL){
        Father = new Index;
        Father->ind = nextInd;
        nextInd++;
        Father->text = newNum.toInt();
        Father->next = Father;
        Father->prev = Father;
        last = Father;
    }
    else {
        Index* newEl = new Index;
        newEl->ind = nextInd;
        nextInd++;
        newEl->text = newNum.toInt();
        last->next = newEl;
        Father->prev = newEl;
        newEl->next = Father;
        newEl->prev = last;
        last = newEl;
    }
    int num = newNum.toInt();
    emit returnText(QString::number(num));

    elementsVector.push_back(newNum.toInt());
}

void Sort::startSort(QString sortType)
{
    // sortType returns the name of sorting

    emit sendToQml(1, 2, "2", "3");
}

void Sort::speedUp()
{

}

void Sort::speedDown()
{

}

} // namespace lab::ui

#ifndef CPPALGO_H
#define CPPALGO_H

#include <QVector>
#include <QDebug>
#include <QString>

class cppAlgo
{
public:
    cppAlgo();
    void defineStartingPoint(const int irow,const int icol);
    QString getStartingPoint();
    void EnQueue(const int irow, const int icol, const double cost);
    int getQueueLength();
    int getDeQueue();
    bool coversWholeSpace(const QVector<QVector<double>> &myShapeMatrix);
    QString getQueueEntry(const int id);
    void eraseQueue();
    bool checkPointOccupencyInMatrix(const QVector<QVector<double>> &myMatrixOccupency, const int irow, const int icol);
    bool checkPointOccupencyInNodeList(const int irow, const int icol);
    bool checkPointOccupency(const QVector<QVector<double>> &myMatrixOccupency, const int irow, const int icol);
    bool checkPointInsideMatrix(const QVector<QVector<double>> &myMatrixOccupency, const int irow, const int icol);
    bool checkNewPointIsAcceptable(const QVector<QVector<double>> &myMatrixOccupency, const int irow, const int icol);
    void addPointToNodeList(const int irow, const int icol);
    void addPointToOccupencyMatrix(QVector<QVector<double>> &myMatrixOccupency,const int irow, const int icol);
    QString getNodeListItem(const int id);
    void clearNodeList();
    int getNodeListSize();
    void addNode(QVector<QVector<int>> &nodeListTemp, const int iNewRow, const int iNewCol);
    void clearAllNode(QVector<QVector<int>> &nodeListTemp);
    QString getLastMoveDirection();
    int getRowShift(const QString &nextMoves);
    int getColShift(const QString &nextMoves);
    void goStraight(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp);
    void goRight(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp);

    void goRightBack(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp);

    void goLeft(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp);
    void goLeftBack(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp);

    bool checkPointIsCorner(const QVector<QVector<double>> &myMatrixOccupency,const int irow, const int icol);
    bool checkNeighboringCorner(const QVector<QVector<double>> &myMatrixOccupency,const int irow, const int icol);

    int getNumberOfRotationFromList(const QVector<QVector<int>> &nodeListTemp);
    void updateMatrixOccupency(QVector<QVector<double>> &myMatrixOccupency, const QVector<QVector<int>> &nodeListTemp);
    int getNumberOfFreecells(const QVector<QVector<double>> &myMatrixOccupency);
    int getLongestLine(const QVector<QVector<double>> &myMatrixOccupency);

    int findCostG(const QVector<QVector<int>> &nodeListTemp);
    int findCostH(const QVector<QVector<double>> &myMatrixOccupency);
    int findTotalCostF(const QVector<QVector<int>> &nodeListTemp,const QVector<QVector<double>> &myMatrixOccupency);
    void searchThePath(const int iStartRow,const int iStartCol);

private:
    int nStartRow;
    int nStartCol;
    //int numberOfRotation;
    QVector<QVector<int>> nodeList;
    QVector<QVector<int>> priorityQueue;
    QVector<double> priorityQueueCost;
    QString lastMoveDirection;
};

#endif // CPPALGO_H

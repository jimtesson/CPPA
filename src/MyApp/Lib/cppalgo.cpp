#include "cppalgo.h"

cppAlgo::cppAlgo()
{

}

void cppAlgo::defineStartingPoint(const int irow,const int icol){
    if(irow>=0 && icol>=0){
        nStartRow = irow;
        nStartCol = icol;
    }
    else
        qDebug() << "starting point indice cannot be negative, i=" << irow << icol;
        return;
}

QString cppAlgo::getStartingPoint(){
    QString StartingPoint = QString("%1,%2").arg(nStartRow).arg(nStartCol);
    return StartingPoint;
}

void cppAlgo::EnQueue(const int xi, const int yi, const double cost){
    priorityQueue.push_front(QVector<int>());
    priorityQueue[0].push_back(xi);
    priorityQueue[0].push_back(yi);

    priorityQueueCost.push_front(cost);
}

int cppAlgo::getQueueLength(){
    return priorityQueue.size();
}

QString cppAlgo::getQueueEntry(const int id){
    QString queueEntry;

    if(id<=priorityQueue.size()){
        queueEntry = QString("%1,%2,%3").arg(priorityQueue[id][0]).arg( priorityQueue[id][1]).arg(priorityQueueCost[id]);
    }
   else{
        queueEntry = QString("no queue entry");
    }
    return queueEntry;
}

int cppAlgo::getDeQueue(){
    double minCost = 1E10;
    int iQueueMinCost=-1;
    for(int iQueue=0; iQueue<priorityQueue.size(); iQueue++){
        if(priorityQueueCost[iQueue] <= minCost){
            iQueueMinCost = iQueue;
            minCost = priorityQueueCost[iQueue];
        }
    }
    return iQueueMinCost;
}

void cppAlgo::eraseQueue(){

    priorityQueue.clear();
    priorityQueue.squeeze();

    priorityQueueCost.clear();
    priorityQueueCost.squeeze();

}

bool cppAlgo::coversWholeSpace(const QVector<QVector<double>> &myShapeMatrix){

    bool elementIsInTheQueue;

    for(int i=0; i<myShapeMatrix.size(); i++)
    {
        for(int j=0; j<myShapeMatrix[i].size(); j++)
        {
           elementIsInTheQueue = false;
           for(int k=0; k<priorityQueue.size(); k++)
           {
                if((priorityQueue[k][0] == i) && (priorityQueue[k][1] == j)){
                    elementIsInTheQueue = true;
                }
           }
           if(!elementIsInTheQueue){return false;}
        }
    }

    return true;
}

bool cppAlgo::checkPointOccupencyInMatrix(const QVector<QVector<double>> &myMatrixOccupency, int irow, int icol){
    bool occupied= false;
    if(myMatrixOccupency[irow][icol]>0){
        occupied = true;
        }
    return occupied;
}

bool cppAlgo::checkPointOccupencyInNodeList(const int irow, const int icol){
    bool occupied= false;

    for(int k=0; k<nodeList.size(); k++)
    {
         if((nodeList[k][0] == irow) && (nodeList[k][1] == icol)){
             occupied = true;
         }
    }

    return occupied;
}

bool cppAlgo::checkPointOccupency(const QVector<QVector<double>> &myMatrixOccupency, const int irow, const int icol){
    bool occupied = false;
    bool checkMat = checkPointOccupencyInMatrix(myMatrixOccupency, irow, icol);
    bool checkQueu = checkPointOccupencyInNodeList(irow, icol);

    if(checkMat || checkQueu){occupied = true;}

    return occupied ;
}

bool cppAlgo::checkPointInsideMatrix(const QVector<QVector<double>> &myMatrixOccupency, const int irow, const int icol){
    bool insideMatrix = true;
    int matSizeRow = myMatrixOccupency.size();
    int matSizeCol = myMatrixOccupency[0].size();

    if((irow < 0) || (irow >= matSizeRow) || (icol < 0) || (icol >= matSizeCol) )
    {
        insideMatrix = false;
    }

    return insideMatrix ;
}

bool cppAlgo::checkNewPointIsAcceptable(const QVector<QVector<double>> &myMatrixOccupency, const int iNewRow, const int iNewCol){
    bool NewPointIsAcceptable = false;
    if(checkPointInsideMatrix(myMatrixOccupency, iNewRow, iNewCol))
    {
        if(!checkPointOccupency(myMatrixOccupency, iNewRow, iNewCol))
            { NewPointIsAcceptable = true;}
    }
    return NewPointIsAcceptable;
}

void cppAlgo::addPointToNodeList(const int irow, const int icol){

    nodeList.push_back(QVector<int>());
    nodeList.back().push_back(irow);
    nodeList.back().push_back(icol);

}

void cppAlgo::addPointToOccupencyMatrix(QVector<QVector<double>> &myMatrixOccupency,const int irow, const int icol){
    if(checkPointInsideMatrix(myMatrixOccupency, irow, icol))
    {
        myMatrixOccupency[irow][icol] = 1;
    }
}

QString cppAlgo::getNodeListItem(const int id){
    return QString("%1,%2").arg(nodeList[id][0]).arg( nodeList[id][1]);
}

void cppAlgo::clearNodeList(){

    nodeList.clear();
    nodeList.squeeze();
}

int cppAlgo::getNodeListSize(){

    return nodeList.size();
}

QString cppAlgo::getLastMoveDirection(){
    lastMoveDirection = QString("");
    if(nodeList.size()<2){return QString("");}
    else
    {
        int idLastMove = nodeList.size()-1;
        int NSshift = nodeList[idLastMove][0]-nodeList[idLastMove-1][0];
        int EWshift = nodeList[idLastMove][1]-nodeList[idLastMove-1][1];

        if(NSshift>0){lastMoveDirection += QString("S");}
        else if(NSshift<0){lastMoveDirection += QString("N");}

        if(EWshift>0){lastMoveDirection += QString("E");}
        else if(EWshift<0){lastMoveDirection += QString("W");}

        return lastMoveDirection;
    }
}

int cppAlgo::getRowShift(const QString &nextMoves){
    int iRowShift=-999;

    if(lastMoveDirection == QString("N"))
    {
        if(nextMoves==QString("straight")){iRowShift = -1;}
        if(nextMoves==QString("left")){iRowShift = 0;}
        if(nextMoves==QString("right")){iRowShift = 0;}
        if(nextMoves==QString("back")){iRowShift = 1;}
    }
    else if(lastMoveDirection == QString("S")){
        if(nextMoves==QString("straight")){iRowShift = 1;}
        if(nextMoves==QString("left")){iRowShift = 0;}
        if(nextMoves==QString("right")){iRowShift = 0;}
        if(nextMoves==QString("back")){iRowShift = -1;}
    }
    else if(lastMoveDirection == QString("E")){
        if(nextMoves==QString("straight")){iRowShift = 0;}
        if(nextMoves==QString("left")){iRowShift = -1;}
        if(nextMoves==QString("right")){iRowShift = 1;}
        if(nextMoves==QString("back")){iRowShift = 0;}
    }
    else if(lastMoveDirection == QString("W")){
        if(nextMoves==QString("straight")){iRowShift = 0;}
        if(nextMoves==QString("left")){iRowShift = 1;}
        if(nextMoves==QString("right")){iRowShift = -1;}
        if(nextMoves==QString("back")){iRowShift = 0;}
    }
    else if(lastMoveDirection == QString("")){// default move is Eastward
        if(nextMoves==QString("straight")){iRowShift = 0;}
        if(nextMoves==QString("left")){iRowShift = -1;}
        if(nextMoves==QString("right")){iRowShift = 1;}
        if(nextMoves==QString("back")){iRowShift = 0;}
    }
    return iRowShift;
}
int cppAlgo::getColShift(const QString &nextMoves){
    int iColShift=-999;

    if(lastMoveDirection == QString("N"))
    {
        if(nextMoves==QString("straight")){iColShift = 0;}
        if(nextMoves==QString("left")){iColShift = -1;}
        if(nextMoves==QString("right")){iColShift = 1;}
        if(nextMoves==QString("back")){iColShift = 0;}
    }
    else if(lastMoveDirection == QString("S"))
    {
        if(nextMoves==QString("straight")){iColShift = 0;}
        if(nextMoves==QString("left")){iColShift = 1;}
        if(nextMoves==QString("right")){iColShift = -1;}
        if(nextMoves==QString("back")){iColShift = 0;}
    }
    else if(lastMoveDirection == QString("E"))
    {
        if(nextMoves==QString("straight")){iColShift = 1;}
        if(nextMoves==QString("left")){iColShift = 0;}
        if(nextMoves==QString("right")){iColShift = 0;}
        if(nextMoves==QString("back")){iColShift = -1;}
    }
    else if(lastMoveDirection == QString("W"))
    {
        if(nextMoves==QString("straight")){iColShift = -1;}
        if(nextMoves==QString("left")){iColShift = 0;}
        if(nextMoves==QString("right")){iColShift = 0;}
        if(nextMoves==QString("back")){iColShift = 1;}
    }
    else if(lastMoveDirection == QString("")) // default move is Eastward
    {
        if(nextMoves==QString("straight")){iColShift = 1;}
        if(nextMoves==QString("left")){iColShift = 0;}
        if(nextMoves==QString("right")){iColShift = 0;}
        if(nextMoves==QString("back")){iColShift = -1;}
    }
    return iColShift;
}

void cppAlgo::addNode(QVector<QVector<int>> &nodeListTemp, const int iNewRow, const int iNewCol){

    nodeListTemp.push_back(QVector<int>());
    nodeListTemp.back().push_back(iNewRow);
    nodeListTemp.back().push_back(iNewCol);
}

void cppAlgo::clearAllNode(QVector<QVector<int>> &nodeListTemp){

    nodeListTemp.clear();
    nodeListTemp.squeeze();
}


void cppAlgo::goStraight(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp){
        if(nodeList.empty()){return;}
        int idLastMove = nodeList.size()-1;
        int iRow = nodeList[idLastMove][0];
        int iCol = nodeList[idLastMove][1];
        int iNewRow = iRow; int iNewCol = iCol;
        int iColShift = 0;
        int iRowShift = 0;
        bool stopLoop = false;
        QString direction = "straight";

        iColShift = getColShift(direction);
        iRowShift = getRowShift(direction);

        while(!stopLoop)
        {
            iNewCol+= iColShift;
            iNewRow += iRowShift;

            if(checkNewPointIsAcceptable(myMatrixOccupency, iNewRow, iNewCol))
            {
                addNode(nodeListTemp, iNewRow, iNewCol);
            }
            else
            {
               stopLoop = true;
            }

            if(checkNeighboringCorner(myMatrixOccupency, iNewRow, iNewCol))
            {
               stopLoop = true;
            }
        }
}

void cppAlgo::goLeft(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp){
        if(nodeList.empty()){return;}
        int idLastMove = nodeList.size()-1;
        int iRow = nodeList[idLastMove][0];
        int iCol = nodeList[idLastMove][1];
        int iNewRow = iRow; int iNewCol = iCol;
        int iColShift = 0;
        int iRowShift = 0;
        bool stopLoop = false;
        QString direction = "left";

        iColShift = getColShift(direction);
        iRowShift = getRowShift(direction);

        while(!stopLoop)
        {
            iNewCol+= iColShift;
            iNewRow += iRowShift;

            if(checkNewPointIsAcceptable(myMatrixOccupency, iNewRow, iNewCol))
            {
                addNode(nodeListTemp, iNewRow, iNewCol);
            }
            else
            {
               stopLoop = true;
            }

            if(checkNeighboringCorner(myMatrixOccupency, iNewRow, iNewCol))
            {
               stopLoop = true;
            }
        }
}

void cppAlgo::goRight(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp){
        if(nodeList.empty()){return;}
        int idLastMove = nodeList.size()-1;
        int iRow = nodeList[idLastMove][0];
        int iCol = nodeList[idLastMove][1];
        int iNewRow = iRow; int iNewCol = iCol;
        int iColShift = 0;
        int iRowShift = 0;
        bool stopLoop = false;
        QString direction = "right";

        iColShift = getColShift(direction);
        iRowShift = getRowShift(direction);

        while(!stopLoop)
        {
            iNewCol+= iColShift;
            iNewRow += iRowShift;

            if(checkNewPointIsAcceptable(myMatrixOccupency, iNewRow, iNewCol))
            {
                addNode(nodeListTemp, iNewRow, iNewCol);
            }
            else
            {
               stopLoop = true;
            }

            if(checkNeighboringCorner(myMatrixOccupency, iNewRow, iNewCol))
            {
               stopLoop = true;
            }
        }
}

void cppAlgo::goLeftBack(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp){
        if(nodeList.empty()){return;}
        int idLastMove = nodeList.size()-1;
        int iRow = nodeList[idLastMove][0];
        int iCol = nodeList[idLastMove][1];
        int iNewRow = iRow; int iNewCol = iCol;
        int iColShift = 0;
        int iRowShift = 0;
        bool stopLoop = false;

        // first move is left
        QString direction = "left";

        iColShift = getColShift(direction);
        iRowShift = getRowShift(direction);
        iNewCol+= iColShift;
        iNewRow += iRowShift;
        if(checkNewPointIsAcceptable(myMatrixOccupency, iNewRow, iNewCol))
        {
            addNode(nodeListTemp, iNewRow, iNewCol);
            if(checkNeighboringCorner(myMatrixOccupency, iNewRow, iNewCol))
            {
               return;
            }
        }
        else {return;}

        // second move is backward
        direction = "back";
        iColShift = getColShift(direction);
        iRowShift = getRowShift(direction);
        while(!stopLoop)
        {
            iNewCol+= iColShift;
            iNewRow += iRowShift;

            if(checkNewPointIsAcceptable(myMatrixOccupency, iNewRow, iNewCol))
            {
                addNode(nodeListTemp, iNewRow, iNewCol);
            }
            else
            {
               stopLoop = true;
            }

            if(checkNeighboringCorner(myMatrixOccupency, iNewRow, iNewCol))
            {
               stopLoop = true;
            }
        }
}


void cppAlgo::goRightBack(const QVector<QVector<double>> &myMatrixOccupency, QVector<QVector<int>> &nodeListTemp){
        if(nodeList.empty()){return;}
        int idLastMove = nodeList.size()-1;
        int iRow = nodeList[idLastMove][0];
        int iCol = nodeList[idLastMove][1];
        int iNewRow = iRow; int iNewCol = iCol;
        int iColShift = 0;
        int iRowShift = 0;
        bool stopLoop = false;

        // first move is left
        QString direction = "right";

        iColShift = getColShift(direction);
        iRowShift = getRowShift(direction);
        iNewCol+= iColShift;
        iNewRow += iRowShift;
        if(checkNewPointIsAcceptable(myMatrixOccupency, iNewRow, iNewCol))
        {
            addNode(nodeListTemp, iNewRow, iNewCol);
            if(checkNeighboringCorner(myMatrixOccupency, iNewRow, iNewCol))
            {
               return;
            }
        }
        else {return;}

        // second move is backward
        direction = "back";
        iColShift = getColShift(direction);
        iRowShift = getRowShift(direction);
        while(!stopLoop)
        {
            iNewCol+= iColShift;
            iNewRow += iRowShift;

            if(checkNewPointIsAcceptable(myMatrixOccupency, iNewRow, iNewCol))
            {
                addNode(nodeListTemp, iNewRow, iNewCol);
            }
            else
            {
               stopLoop = true;
            }

            if(checkNeighboringCorner(myMatrixOccupency, iNewRow, iNewCol))
            {
               stopLoop = true;
            }
        }
}

bool cppAlgo::checkPointIsCorner(const QVector<QVector<double>> &myMatrixOccupency,const int irow, const int icol){

    int nColMatrix = myMatrixOccupency[0].size();
    int nRowMatrix = myMatrixOccupency.size();
    int sumCorner;
    if(myMatrixOccupency[irow][icol]>0)
    {
        if((irow>0)&&(icol>0))
        {
            // Top left corner
            sumCorner = int(myMatrixOccupency[irow][icol-1] + myMatrixOccupency[irow-1][icol-1] + myMatrixOccupency[irow-1][icol]);
            if(sumCorner==0){return true;}
        }
        if((irow>0)&&(icol<(nColMatrix-1)))
        {
            // Top right corner
            sumCorner = int(myMatrixOccupency[irow][icol+1] + myMatrixOccupency[irow-1][icol+1] + myMatrixOccupency[irow-1][icol]);
            if(sumCorner==0){return true;}
        }
        if((irow<(nRowMatrix-1))&&(icol>0))
        {
            // Bottom left corner
            sumCorner = int(myMatrixOccupency[irow][icol-1] + myMatrixOccupency[irow+1][icol-1] + myMatrixOccupency[irow+1][icol]);
            if(sumCorner==0){return true;}
        }
        if((irow<(nRowMatrix-1))&&(icol<(nColMatrix-1)))
        {
        // Bottom right corner
            sumCorner = int(myMatrixOccupency[irow][icol+1] + myMatrixOccupency[irow+1][icol+1] + myMatrixOccupency[irow+1][icol]);
            if(sumCorner==0){return true;}
        }

    }

    return false;
}

bool cppAlgo::checkNeighboringCorner(const QVector<QVector<double>> &myMatrixOccupency,const int irow, const int icol){
    bool NeighboringCorner=false;
    QVector<int> iRowTest;
    QVector<int> iColTest;
    int nRowMatrix = myMatrixOccupency.size();
    int nColMatrix = myMatrixOccupency[0].size();

    // check around the desired point
    // topleft
    iRowTest.push_back(irow-1);
    iColTest.push_back(icol-1);
    // top
    iRowTest.push_back(irow-1);
    iColTest.push_back(icol);
    // top right
    iRowTest.push_back(irow-1);
    iColTest.push_back(icol+1);
    // left
    iRowTest.push_back(irow);
    iColTest.push_back(icol-1);
    // right
    iRowTest.push_back(irow);
    iColTest.push_back(icol+1);
    // bottom left
    iRowTest.push_back(irow+1);
    iColTest.push_back(icol-1);
    // bottom
    iRowTest.push_back(irow+1);
    iColTest.push_back(icol);
    // bottom right
    iRowTest.push_back(irow+1);
    iColTest.push_back(icol+1);

    for(int id=1;id<iRowTest.size();id++)
    {
        if((iRowTest[id]>=0) && (iRowTest[id]<nRowMatrix) && (iColTest[id]>=0) && (iColTest[id]<nColMatrix))
        {
            NeighboringCorner = checkPointIsCorner(myMatrixOccupency,iRowTest[id],iColTest[id]);
            if(NeighboringCorner){return true;}
        }
    }


    return false;
}

int cppAlgo::getNumberOfRotationFromList(const QVector<QVector<int>> &nodeListTemp)
{
    int RowDirCurrentMove = 0;
    int ColDirCurrentMove = 0;
    int numberOfRotation = 0;

    for(int i=2;i<nodeListTemp.size();i++)
    {
        RowDirCurrentMove = abs(nodeListTemp[i][0] - nodeListTemp[i-2][0]);
        ColDirCurrentMove = abs(nodeListTemp[i][1] - nodeListTemp[i-2][1]);
        if( (RowDirCurrentMove > 0) && (ColDirCurrentMove > 0) )
        {
            numberOfRotation += 1;
        }
     }
    return numberOfRotation;
}

void cppAlgo::updateMatrixOccupency(QVector<QVector<double>> &myMatrixOccupency, const QVector<QVector<int>> &nodeListTemp)
{
    int iRow;
    int iCol;

    for(int i=0; i<nodeListTemp.size();i++)
    {
        iRow = nodeListTemp[i][0];
        iCol = nodeListTemp[i][1];
        myMatrixOccupency[iRow][iCol] = 1;
    }
}

int cppAlgo::getNumberOfFreecells(const QVector<QVector<double>> &myMatrixOccupency)
{
    int freeCellCount = 0;

    for(int i=0; i<myMatrixOccupency.size();i++)
    {
        for(int j=0; j<myMatrixOccupency[i].size();j++)
        {
            if(myMatrixOccupency[i][j]<=0)
            {
                ++freeCellCount;
            }
        }
    }
    return freeCellCount;
}

int cppAlgo::getLongestLine(const QVector<QVector<double>> &myMatrixOccupency)
{
    int longestLine = 0;
    int rowLength = 0;
    int colLength = 0;

    // row analysis
    for(int i=0; i<myMatrixOccupency.size();i++)
    {
        rowLength = 0;
        for(int j=0; j<myMatrixOccupency[i].size();j++)
        {

            if(myMatrixOccupency[i][j]<=0)
            {
                ++rowLength;
            }
            else {rowLength = 0;}

        }
        if(rowLength > longestLine){longestLine = rowLength;}
    }

    // col analysis
    for(int i=0; i<myMatrixOccupency[0].size();i++)
    {
        colLength = 0;
        for(int j=0; j<myMatrixOccupency.size();j++)
        {

            if(myMatrixOccupency[j][i]<=0)
            {
                ++colLength;
            }
            else {rowLength = 0;}

        }
        if(colLength > longestLine){longestLine = colLength;}
    }

    return longestLine;
}


int cppAlgo::findCostG(const QVector<QVector<int>> &nodeListTemp){
    // number of rotations up to now
    return getNumberOfRotationFromList(nodeListTemp);
}

int cppAlgo::findCostH(const QVector<QVector<double>> &myMatrixOccupency){
    // Heuristic for the futur number of rotations
    int longestLine = getLongestLine(myMatrixOccupency);
    int numberFreeCell = getNumberOfFreecells(myMatrixOccupency);

    int costH = int(2*numberFreeCell/longestLine-2);

    return costH;
}

int cppAlgo::findTotalCostF(const QVector<QVector<int>> &nodeListTemp,const QVector<QVector<double>> &myMatrixOccupency){
    int TotalCostF = findCostH(myMatrixOccupency) + findCostG(nodeListTemp);
    return TotalCostF;
}


void cppAlgo::searchThePath(const int iStartRow,const int iStartCol){

    defineStartingPoint(iStartRow, iStartCol);
    // cost of the starting point

    findTotalCostF();
    EnQueue(iStartRow,  iStartCol, const double cost)

}

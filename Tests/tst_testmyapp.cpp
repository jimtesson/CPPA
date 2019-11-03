#include <QtTest>
#include "iashape.h"
#include "cppalgo.h"

// add necessary includes here

class TestmyApp : public QObject
{
    Q_OBJECT

public:
    TestmyApp();
    ~TestmyApp();
private:
    int nrow;
    int ncol;
    iaShape myShape;
    cppAlgo myCppAlgo;

private slots:

    void iashape_test_MatrixInitialization();
    void iashape_test_getSizeRow();
    void iashape_test_getSizeCol();
    void iashape_test_changeValueAt();
    void iashape_test_getMyShapeMatrixCopy();

    void cppalgo_test_defineStartingPoint();
    void cppalgo_test_getQueueLength();
    void cppalgo_test_getQueueEntry();
    void cppalgo_test_getDeQueue();
    void cppalgo_test_eraseQueue();
    void cppalgo_test_coversWholeSpace();
    void cppalgo_test_getNodeListItem();
    void cppalgo_test_clearNodeList();
    void cppalgo_test_checkPointOccupencyInNodeList();
    void cppalgo_test_checkPointOccupencyInMatrix();
    void cppalgo_test_checkPointOccupency();
    void cppalgo_test_checkPointInsideMatrix();
    void cppalgo_test_getLastMoveDirection();
    void cppalgo_test_getColShift();
    void cppalgo_test_getRowShift();
    void cppalgo_test_goStraight();
    void cppalgo_test_goLeft();
    void cppalgo_test_goRight();
    void cppalgo_test_goLeftBack();
    void cppalgo_test_goRightBack();
    void cppalgo_test_addPointToOccupencyMatrix();
    void cppalgo_test_getNumberOfRotationFromList();
    void cppalgo_test_checkPointIsCorner();
    void cppalgo_test_checkNeighboringCorner();
    void cppalgo_test_getNumberOfFreecells();
    void cppalgo_test_updateMatrixOccupency();
    void cppalgo_test_getLongestLine();
    void cppalgo_test_findTotalCostF();
    void cppalgo_test_findTotalCostH();


    //void cppalgo_test_deQueue();

};

TestmyApp::TestmyApp()
{
    nrow = 4;
    ncol = 5;
    myShape.initializeMatrix(nrow, ncol);
}

TestmyApp::~TestmyApp()
{

}


void TestmyApp::iashape_test_MatrixInitialization()
{
        for(int i=0;i<nrow;i++)
        {
            for(int j=0;j<ncol;j++){
               QCOMPARE(myShape.getValueAt(i, j),0);
            }
        }
}

void TestmyApp::iashape_test_getSizeRow(){

    QCOMPARE(myShape.getSizeRow(),nrow);
}

void TestmyApp::iashape_test_getSizeCol(){

    QCOMPARE(myShape.getSizeCol(),ncol);
}


void TestmyApp::iashape_test_changeValueAt(){


    int i=0; int j=1; double val=-999.999;
    myShape.changeValueAt(i,j,val);

    QCOMPARE(myShape.getValueAt(i,j),val);
    myShape.initializeMatrix(nrow, ncol);

}

void TestmyApp::iashape_test_getMyShapeMatrixCopy(){

    QVector<QVector<double>> MyShapeMatrixCopy;

    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    for(int i=0;i<nrow;i++)
    {
        for(int j=0;j<ncol;j++){
            QCOMPARE(MyShapeMatrixCopy[i][j],myShape.getValueAt(i,j));
        }
    }

}

// cppalgo

void TestmyApp::cppalgo_test_defineStartingPoint(){
    int i=10; int j=2;
    myCppAlgo.defineStartingPoint(i,j);
    QCOMPARE(myCppAlgo.getStartingPoint(),QString("10,2"));

}

void TestmyApp::cppalgo_test_getQueueLength(){

    QCOMPARE(myCppAlgo.getQueueLength(),0);

    int xi = 0; int yi = 0; double icost=2.99;
    myCppAlgo.EnQueue(xi,yi,icost);
    QCOMPARE(myCppAlgo.getQueueLength(),1);

    xi = 1; yi = 0; icost=1.11;
    myCppAlgo.EnQueue(xi,yi,icost);
    QCOMPARE(myCppAlgo.getQueueLength(),2);
}

void TestmyApp::cppalgo_test_getQueueEntry(){
    int xi = 0; int yi = 0; double icost=3.99;
    myCppAlgo.EnQueue(xi,yi,icost);
    QCOMPARE(QString(myCppAlgo.getQueueEntry(0)),QString("0,0,3.99"));

    xi = 1; yi = 2; icost=5.99;
    myCppAlgo.EnQueue(xi,yi,icost);
    QCOMPARE(QString(myCppAlgo.getQueueEntry(0)),QString("1,2,5.99"));
    QCOMPARE(QString(myCppAlgo.getQueueEntry(1)),QString("0,0,3.99"));
}

void TestmyApp::cppalgo_test_getDeQueue(){
    int xi = 10; int yi = 100; double icost=0.001;
    myCppAlgo.EnQueue(xi,yi,icost);
    QCOMPARE(myCppAlgo.getDeQueue(),0);

    myCppAlgo.EnQueue(0,0,0.1);
    myCppAlgo.EnQueue(0,0,0.2);
    myCppAlgo.EnQueue(0,0,0.3);
    QCOMPARE(myCppAlgo.getDeQueue(),3);
    QCOMPARE(QString(myCppAlgo.getQueueEntry(myCppAlgo.getDeQueue())),QString("10,100,0.001"));

}

void TestmyApp::cppalgo_test_eraseQueue(){
    myCppAlgo.eraseQueue();
     QCOMPARE(myCppAlgo.getQueueLength(),0);
}

void TestmyApp::cppalgo_test_coversWholeSpace(){
    // test empty queue
    myCppAlgo.eraseQueue();
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    QCOMPARE(myCppAlgo.coversWholeSpace(MyShapeMatrixCopy),false);

    // test queue covers whole space
    for(int i=0;i<nrow;i++)
    {
        for(int j=0;j<ncol;j++){
           myCppAlgo.EnQueue(i,j,1.0);
        }
    }
    QCOMPARE(myCppAlgo.coversWholeSpace(MyShapeMatrixCopy),true);

     // test queue partially covers the space
    myCppAlgo.eraseQueue();
    for(int i=0;i<nrow;i++)
    {
           myCppAlgo.EnQueue(i,0,1.0);
    }

    QCOMPARE(myCppAlgo.coversWholeSpace(MyShapeMatrixCopy),false);

}

void TestmyApp::cppalgo_test_getNodeListItem(){
    myCppAlgo.addPointToNodeList(0, 0);
    QCOMPARE(myCppAlgo.getNodeListItem(0),QString("0,0"));
    myCppAlgo.addPointToNodeList(1, 2);
    QCOMPARE(myCppAlgo.getNodeListItem(0),QString("0,0"));
    QCOMPARE(myCppAlgo.getNodeListItem(1),QString("1,2"));
}

void TestmyApp::cppalgo_test_clearNodeList(){

    QCOMPARE(myCppAlgo.getNodeListSize(),2);
    myCppAlgo.clearNodeList();
    QCOMPARE(myCppAlgo.getNodeListSize(),0);
}

void TestmyApp::cppalgo_test_checkPointOccupencyInNodeList(){
    myCppAlgo.addPointToNodeList(0, 0);
    QCOMPARE(myCppAlgo.checkPointOccupencyInNodeList(0,0),true);
    myCppAlgo.addPointToNodeList(1, 2);
    QCOMPARE(myCppAlgo.checkPointOccupencyInNodeList(1,2),true);
    QCOMPARE(myCppAlgo.checkPointOccupencyInNodeList(100,100),false);

}

void TestmyApp::cppalgo_test_checkPointOccupencyInMatrix(){

    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);

    for(int i = 0; i<MyShapeMatrixCopy.size(); i++){
        for(int j = 0; j<MyShapeMatrixCopy[i].size(); j++){
            MyShapeMatrixCopy[i][j] = 1.0;
            QCOMPARE(myCppAlgo.checkPointOccupencyInMatrix(MyShapeMatrixCopy, i, j),true);
            MyShapeMatrixCopy[i][j] = 0.0;
            QCOMPARE(myCppAlgo.checkPointOccupencyInMatrix(MyShapeMatrixCopy, i, j),false);
        }
    }
}

void TestmyApp::cppalgo_test_checkPointOccupency(){
    // create the matrix
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    int irow = 0; int icol=0;
    MyShapeMatrixCopy[irow][icol] = 0.0;
    // clear the node list
    myCppAlgo.clearNodeList();

    QCOMPARE(myCppAlgo.checkPointOccupency(MyShapeMatrixCopy, irow, icol),false);

    MyShapeMatrixCopy[irow][icol] = 1.0;
    QCOMPARE(myCppAlgo.checkPointOccupency(MyShapeMatrixCopy, irow, icol),true);

    MyShapeMatrixCopy[irow][icol] = 0.0;
    myCppAlgo.addPointToNodeList(irow, icol);
    QCOMPARE(myCppAlgo.checkPointOccupency(MyShapeMatrixCopy, irow, icol),true);

}

void TestmyApp::cppalgo_test_checkPointInsideMatrix(){
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    int irow = 0; int icol=0;
    QCOMPARE(myCppAlgo.checkPointInsideMatrix(MyShapeMatrixCopy, irow, icol),true);
    irow = 2; icol=3;
    QCOMPARE(myCppAlgo.checkPointInsideMatrix(MyShapeMatrixCopy, irow, icol),true);
    irow = 10; icol=100;
    QCOMPARE(myCppAlgo.checkPointInsideMatrix(MyShapeMatrixCopy, irow, icol),false);
}

void TestmyApp::cppalgo_test_getLastMoveDirection(){
    myCppAlgo.clearNodeList();
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString());
    myCppAlgo.addPointToNodeList(0, 0); // path is already passing by the coordinate 0,4
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString());
    myCppAlgo.addPointToNodeList(0, 1); // start node coordinate is 0,0
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
    myCppAlgo.addPointToNodeList(0, 0); // start node coordinate is 0,0
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
    myCppAlgo.addPointToNodeList(1, 0); // start node coordinate is 0,0
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
    myCppAlgo.addPointToNodeList(0, 0); // start node coordinate is 0,0
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));

}

void TestmyApp::cppalgo_test_getColShift()
{   QString move = "straight";
        //Eastward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(0, 1);
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
        QCOMPARE(myCppAlgo.getColShift(move),1);
        // westward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 1);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
        QCOMPARE(myCppAlgo.getColShift(move),-1);
        // Northward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
        QCOMPARE(myCppAlgo.getColShift(move),0);
        // southward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
        QCOMPARE(myCppAlgo.getColShift(move),0);

    move = "left";
        //Eastward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(0, 1);
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
        QCOMPARE(myCppAlgo.getColShift(move),0);
        // westward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 1);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
        QCOMPARE(myCppAlgo.getColShift(move),0);
        // Northward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
        QCOMPARE(myCppAlgo.getColShift(move),-1);
        // southward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
        QCOMPARE(myCppAlgo.getColShift(move),1);

    move = "right";
        //Eastward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(0, 1);
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
        QCOMPARE(myCppAlgo.getColShift(move),0);
        // westward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 1);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
        QCOMPARE(myCppAlgo.getColShift(move),0);
        // Northward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
        QCOMPARE(myCppAlgo.getColShift(move),1);
        // southward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
        QCOMPARE(myCppAlgo.getColShift(move),-1);

    move = "back";
        //Eastward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(0, 1);
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
        QCOMPARE(myCppAlgo.getColShift(move),-1);
        // westward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 1);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
        QCOMPARE(myCppAlgo.getColShift(move),1);
        // Northward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
        QCOMPARE(myCppAlgo.getColShift(move),0);
        // southward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
        QCOMPARE(myCppAlgo.getColShift(move),0);
}

void TestmyApp::cppalgo_test_getRowShift()
{   QString move = "straight";
        //Eastward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(0, 1);
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
        QCOMPARE(myCppAlgo.getRowShift(move),0);
        // westward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 1);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
        QCOMPARE(myCppAlgo.getRowShift(move),0);
        // Northward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
        QCOMPARE(myCppAlgo.getRowShift(move),-1);
        // southward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
        QCOMPARE(myCppAlgo.getRowShift(move),1);

    move = "left";
        //Eastward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(0, 1);
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
        QCOMPARE(myCppAlgo.getRowShift(move),-1);
        // westward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 1);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
        QCOMPARE(myCppAlgo.getRowShift(move),1);
        // Northward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
        QCOMPARE(myCppAlgo.getRowShift(move),0);
        // southward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
        QCOMPARE(myCppAlgo.getRowShift(move),0);

    move = "right";
        //Eastward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(0, 1);
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
        QCOMPARE(myCppAlgo.getRowShift(move),1);
        // westward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 1);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
        QCOMPARE(myCppAlgo.getRowShift(move),-1);
        // Northward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
        QCOMPARE(myCppAlgo.getRowShift(move),0);
        // southward
        myCppAlgo.clearNodeList();
        myCppAlgo.addPointToNodeList(0, 0);
        myCppAlgo.addPointToNodeList(1, 0);
        myCppAlgo.getLastMoveDirection();
        QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
        QCOMPARE(myCppAlgo.getRowShift(move),0);

    move = "back";
       //Eastward
       myCppAlgo.clearNodeList();
       myCppAlgo.addPointToNodeList(0, 0);
       myCppAlgo.addPointToNodeList(0, 1);
       QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("E"));
       QCOMPARE(myCppAlgo.getRowShift(move),0);
       // westward
       myCppAlgo.clearNodeList();
       myCppAlgo.addPointToNodeList(0, 1);
       myCppAlgo.addPointToNodeList(0, 0);
       myCppAlgo.getLastMoveDirection();
       QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
       QCOMPARE(myCppAlgo.getRowShift(move),0);
       // Northward
       myCppAlgo.clearNodeList();
       myCppAlgo.addPointToNodeList(1, 0);
       myCppAlgo.addPointToNodeList(0, 0);
       myCppAlgo.getLastMoveDirection();
       QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
       QCOMPARE(myCppAlgo.getRowShift(move),1);
       // southward
       myCppAlgo.clearNodeList();
       myCppAlgo.addPointToNodeList(0, 0);
       myCppAlgo.addPointToNodeList(1, 0);
       myCppAlgo.getLastMoveDirection();
       QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
       QCOMPARE(myCppAlgo.getRowShift(move),-1);
}


void TestmyApp::cppalgo_test_goStraight()
{
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(0, 0); // start node coordinate is 0,0
    myCppAlgo.getLastMoveDirection();

    // From Eastward direction
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),4);
    for(int i=0; i<nodeListTemp.size(); i++)
    {
        QCOMPARE(nodeListTemp[i][0],0);
        QCOMPARE(nodeListTemp[i][1],i+1);
    }

    // From Westward direction
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    nodeListTemp.clear();
    myCppAlgo.clearNodeList();
    myCppAlgo.addPointToNodeList(0, 4);
    myCppAlgo.addPointToNodeList(0, 3);
    myCppAlgo.getLastMoveDirection();
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("W"));
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),3);
    QCOMPARE(nodeListTemp[0][0],0);
    QCOMPARE(nodeListTemp[0][1],2);
    QCOMPARE(nodeListTemp[1][0],0);
    QCOMPARE(nodeListTemp[1][1],1);
    QCOMPARE(nodeListTemp[2][0],0);
    QCOMPARE(nodeListTemp[2][1],0);

    // From Southward direction
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    nodeListTemp.clear();
    myCppAlgo.clearNodeList();
    myCppAlgo.addPointToNodeList(0, 0);
    myCppAlgo.addPointToNodeList(1, 0);
    myCppAlgo.getLastMoveDirection();
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("S"));
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);
    QCOMPARE(nodeListTemp[0][0],2);
    QCOMPARE(nodeListTemp[0][1],0);
    QCOMPARE(nodeListTemp[1][0],3);
    QCOMPARE(nodeListTemp[1][1],0);

    // From Northward direction
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    nodeListTemp.clear();
    myCppAlgo.clearNodeList();
    myCppAlgo.addPointToNodeList(3, 0);
    myCppAlgo.addPointToNodeList(2, 0);
    myCppAlgo.getLastMoveDirection();
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);
    QCOMPARE(nodeListTemp[0][0],1);
    QCOMPARE(nodeListTemp[0][1],0);
    QCOMPARE(nodeListTemp[1][0],0);
    QCOMPARE(nodeListTemp[1][1],0);

    // From Northward direction with corner
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    nodeListTemp.clear();
    myCppAlgo.clearNodeList();
    myCppAlgo.addPointToNodeList(3, 0);
    myCppAlgo.addPointToNodeList(2, 0);
    myCppAlgo.getLastMoveDirection();
    QCOMPARE(myCppAlgo.getLastMoveDirection(),QString("N"));
    MyShapeMatrixCopy[0][1] = 1; // add a corner
    myCppAlgo.goStraight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),1);
    QCOMPARE(nodeListTemp[0][0],1);
    QCOMPARE(nodeListTemp[0][1],0);

}

void TestmyApp::cppalgo_test_goLeft()
{
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);

    // coming from Eastward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(2, 0); //
    myCppAlgo.addPointToNodeList(2, 1); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goLeft(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);

    QCOMPARE(nodeListTemp[0][0],1);
    QCOMPARE(nodeListTemp[0][1],1);

    QCOMPARE(nodeListTemp[1][0],0);
    QCOMPARE(nodeListTemp[1][1],1);

    // coming from Westward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(1, 4); //
    myCppAlgo.addPointToNodeList(1, 3); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goLeft(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);

    QCOMPARE(nodeListTemp[0][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],3);// col position of point 1

    QCOMPARE(nodeListTemp[1][0],3);// row position of point 2
    QCOMPARE(nodeListTemp[1][1],3);// col position of point 2

    // coming from Northward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(0, 3); //
    myCppAlgo.addPointToNodeList(1, 3); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goLeft(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),1);

    QCOMPARE(nodeListTemp[0][0],1);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],4);// col position of point 1

    // coming from Southward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(3, 2); //
    myCppAlgo.addPointToNodeList(2, 2); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goLeft(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);

    QCOMPARE(nodeListTemp[0][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],1);// col position of point 1

    QCOMPARE(nodeListTemp[1][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[1][1],0);// col position of point 1

    // coming from Southward direction -  no move possible because of edge matrix
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(3, 0); //
    myCppAlgo.addPointToNodeList(2, 0); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goLeft(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),0);

    // coming from Southward direction with corner
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(3, 2); //
    myCppAlgo.addPointToNodeList(2, 2); //
    myCppAlgo.getLastMoveDirection();
    MyShapeMatrixCopy[3][0] = 1; // add a corner
    myCppAlgo.goLeft(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),1);

    QCOMPARE(nodeListTemp[0][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],1);// col position of point 1

}

void TestmyApp::cppalgo_test_goRight()
{
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);

    // coming from Eastward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(1, 0); //
    myCppAlgo.addPointToNodeList(1, 1); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goRight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);
    QCOMPARE(nodeListTemp[0][0],2);
    QCOMPARE(nodeListTemp[0][1],1);
    QCOMPARE(nodeListTemp[1][0],3);
    QCOMPARE(nodeListTemp[1][1],1);

    // coming from Westward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(2, 4); //
    myCppAlgo.addPointToNodeList(2, 3); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goRight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);

    QCOMPARE(nodeListTemp[0][0],1);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],3);// col position of point 1

    QCOMPARE(nodeListTemp[1][0],0);// row position of point 2
    QCOMPARE(nodeListTemp[1][1],3);// col position of point 2

    // coming from Northward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(0, 3); //
    myCppAlgo.addPointToNodeList(1, 3); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goLeft(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),1);

    QCOMPARE(nodeListTemp[0][0],1);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],4);// col position of point 1


    // coming from Southward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(3, 1); //
    myCppAlgo.addPointToNodeList(2, 1); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goRight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),3);

    QCOMPARE(nodeListTemp[0][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],2);// col position of point 1

    QCOMPARE(nodeListTemp[1][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[1][1],3);// col position of point 1

    QCOMPARE(nodeListTemp[2][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[2][1],4);// col position of point 1

    // coming from Southward direction -  no move possible because of edge matrix
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(3, 5); //
    myCppAlgo.addPointToNodeList(2, 5); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goRight(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),0);
}

void TestmyApp::cppalgo_test_goLeftBack()
{
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);

    // coming from Eastward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(2, 0); //
    myCppAlgo.addPointToNodeList(2, 1); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goLeftBack(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);

    QCOMPARE(nodeListTemp[0][0],1);
    QCOMPARE(nodeListTemp[0][1],1);

    QCOMPARE(nodeListTemp[1][0],1);
    QCOMPARE(nodeListTemp[1][1],0);

    // coming from Westward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(1, 4); //
    myCppAlgo.addPointToNodeList(1, 3); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goLeftBack(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);

    QCOMPARE(nodeListTemp[0][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],3);// col position of point 1

    QCOMPARE(nodeListTemp[1][0],2);// row position of point 2
    QCOMPARE(nodeListTemp[1][1],4);// col position of point 2

    // coming from Westward direction with corner
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(1, 4); //
    myCppAlgo.addPointToNodeList(1, 3); //
    myCppAlgo.getLastMoveDirection();
    MyShapeMatrixCopy[3][3]=1;
    myCppAlgo.goLeftBack(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),1);

    QCOMPARE(nodeListTemp[0][0],2);// row position of point 1
    QCOMPARE(nodeListTemp[0][1],3);// col position of point 1


}

void TestmyApp::cppalgo_test_goRightBack()
{
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);

    // coming from Eastward direction
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(2, 0); //
    myCppAlgo.addPointToNodeList(2, 1); //
    myCppAlgo.getLastMoveDirection();
    myCppAlgo.goRightBack(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),2);

    QCOMPARE(nodeListTemp[0][0],3);
    QCOMPARE(nodeListTemp[0][1],1);

    QCOMPARE(nodeListTemp[1][0],3);
    QCOMPARE(nodeListTemp[1][1],0);

    // coming from Eastward direction with corner
    myCppAlgo.clearNodeList();
    nodeListTemp.clear();
    myCppAlgo.addPointToNodeList(1, 0); //
    myCppAlgo.addPointToNodeList(1, 1); //
    myCppAlgo.getLastMoveDirection();
    MyShapeMatrixCopy[3][0]=1;
    myCppAlgo.goRightBack(MyShapeMatrixCopy,nodeListTemp);
    QCOMPARE(nodeListTemp.size(),1);

    QCOMPARE(nodeListTemp[0][0],2);
    QCOMPARE(nodeListTemp[0][1],1);


}

void TestmyApp::cppalgo_test_addPointToOccupencyMatrix(){
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    int irow = 0; int icol = 0;

    MyShapeMatrixCopy[irow][icol]=0;
    myCppAlgo.addPointToOccupencyMatrix(MyShapeMatrixCopy,irow,icol);
    QCOMPARE(MyShapeMatrixCopy[irow][icol],1);
}

void TestmyApp::cppalgo_test_checkPointIsCorner(){
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);


    MyShapeMatrixCopy[0][0]=0;
    MyShapeMatrixCopy[0][1]=0;
    MyShapeMatrixCopy[0][2]=0;
    MyShapeMatrixCopy[0][3]=0;
    MyShapeMatrixCopy[0][4]=0;
    MyShapeMatrixCopy[1][0]=0;
    MyShapeMatrixCopy[2][0]=0;
    MyShapeMatrixCopy[3][0]=0;
    MyShapeMatrixCopy[1][4]=0;
    MyShapeMatrixCopy[2][4]=0;


    MyShapeMatrixCopy[3][0]=0;
    MyShapeMatrixCopy[3][1]=0;
    MyShapeMatrixCopy[3][2]=0;
    MyShapeMatrixCopy[3][3]=0;
    MyShapeMatrixCopy[3][4]=0;

    MyShapeMatrixCopy[1][1]=1;
    MyShapeMatrixCopy[1][2]=1;
    MyShapeMatrixCopy[1][3]=1;

    MyShapeMatrixCopy[2][1]=1;
    MyShapeMatrixCopy[2][2]=1;
    MyShapeMatrixCopy[2][3]=1;



    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,1,1),true);
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,1,2),false);
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,1,3),true);

    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,2,1),true);
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,2,2),false);
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,2,3),true);

    // corner in the topleft corner of the matrix
    MyShapeMatrixCopy[0][0]=1;
    MyShapeMatrixCopy[1][1]=0;
    MyShapeMatrixCopy[0][1]=0;
    MyShapeMatrixCopy[1][0]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,0,0),true);

    // corner in the bottomleftcorner of the matrix
    MyShapeMatrixCopy[3][0]=1;
    MyShapeMatrixCopy[2][0]=0;
    MyShapeMatrixCopy[2][1]=0;
    MyShapeMatrixCopy[3][1]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,3,0),true);

    // corner in the topright corner of the matrix
    MyShapeMatrixCopy[0][4]=1;
    MyShapeMatrixCopy[0][3]=0;
    MyShapeMatrixCopy[1][3]=0;
    MyShapeMatrixCopy[1][4]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,0,4),true);

    // corner in the bottomright corner of the
    MyShapeMatrixCopy[3][4]=1;
    MyShapeMatrixCopy[3][3]=0;
    MyShapeMatrixCopy[2][3]=0;
    MyShapeMatrixCopy[2][4]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,3,4),true);

    // corner along the left side of the matrix
    MyShapeMatrixCopy[1][0]=1;
    MyShapeMatrixCopy[0][0]=0;
    MyShapeMatrixCopy[0][1]=0;
    MyShapeMatrixCopy[1][1]=0;
    MyShapeMatrixCopy[2][1]=0;
    MyShapeMatrixCopy[2][0]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,1,0),true);

    // corner along the right side of the matrix
    MyShapeMatrixCopy[2][4]=1;
    MyShapeMatrixCopy[1][4]=0;
    MyShapeMatrixCopy[1][3]=0;
    MyShapeMatrixCopy[2][3]=0;
    MyShapeMatrixCopy[3][3]=0;
    MyShapeMatrixCopy[3][4]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,1,0),true);

    // corner along the top side of the matrix
    MyShapeMatrixCopy[0][2]=1;
    MyShapeMatrixCopy[0][1]=0;
    MyShapeMatrixCopy[1][1]=0;
    MyShapeMatrixCopy[1][2]=0;
    MyShapeMatrixCopy[1][3]=0;
    MyShapeMatrixCopy[0][3]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,0,2),true);

    // corner along the bottom side of the matrix
    MyShapeMatrixCopy[3][2]=1;
    MyShapeMatrixCopy[3][1]=0;
    MyShapeMatrixCopy[2][1]=0;
    MyShapeMatrixCopy[2][2]=0;
    MyShapeMatrixCopy[2][3]=0;
    MyShapeMatrixCopy[3][3]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,3,2),true);

    // corner along the top side of the matrix
    MyShapeMatrixCopy[0][0]=1;
    MyShapeMatrixCopy[1][0]=1;
    MyShapeMatrixCopy[2][0]=1;
    MyShapeMatrixCopy[3][0]=1;
    MyShapeMatrixCopy[0][1]=0;
    MyShapeMatrixCopy[1][1]=0;
    MyShapeMatrixCopy[1][1]=0;
    MyShapeMatrixCopy[1][1]=0;
    QCOMPARE(myCppAlgo.checkPointIsCorner(MyShapeMatrixCopy,1,0),false);
}

void TestmyApp::cppalgo_test_checkNeighboringCorner(){
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);

    QCOMPARE(myCppAlgo.checkNeighboringCorner(MyShapeMatrixCopy,0,0),false);

    MyShapeMatrixCopy[0][1]=1; // add a corner
    QCOMPARE(myCppAlgo.checkNeighboringCorner(MyShapeMatrixCopy,0,0),true);
    QCOMPARE(myCppAlgo.checkNeighboringCorner(MyShapeMatrixCopy,1,1),true);
    MyShapeMatrixCopy[0][2]=1; // add a corner
    QCOMPARE(myCppAlgo.checkNeighboringCorner(MyShapeMatrixCopy,1,1),true);
}

void TestmyApp::cppalgo_test_getNumberOfRotationFromList(){

    QVector<QVector<int>> nodeListTemp;
    myCppAlgo.addNode(nodeListTemp,0, 0);
    myCppAlgo.addNode(nodeListTemp,1, 0);
    myCppAlgo.addNode(nodeListTemp,2, 0);
    myCppAlgo.addNode(nodeListTemp,3, 0);
    QCOMPARE(myCppAlgo.getNumberOfRotationFromList(nodeListTemp),0);

    // 1 rotation
    myCppAlgo.clearAllNode(nodeListTemp);
    myCppAlgo.addNode(nodeListTemp,0, 0);
    myCppAlgo.addNode(nodeListTemp,1, 0);
    myCppAlgo.addNode(nodeListTemp,1, 1);
    myCppAlgo.addNode(nodeListTemp,1, 2);
    QCOMPARE(myCppAlgo.getNumberOfRotationFromList(nodeListTemp),1);

    // 2 rotation
    myCppAlgo.clearAllNode(nodeListTemp);
    myCppAlgo.addNode(nodeListTemp,0, 0);
    myCppAlgo.addNode(nodeListTemp,1, 0);
    myCppAlgo.addNode(nodeListTemp,1, 1);
    myCppAlgo.addNode(nodeListTemp,1, 2);
    myCppAlgo.addNode(nodeListTemp,2, 2);
    QCOMPARE(myCppAlgo.getNumberOfRotationFromList(nodeListTemp),2);

}

void TestmyApp::cppalgo_test_getNumberOfFreecells()
{
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    QCOMPARE(myCppAlgo.getNumberOfFreecells(MyShapeMatrixCopy),20);
    MyShapeMatrixCopy[0][1]=1;
    QCOMPARE(myCppAlgo.getNumberOfFreecells(MyShapeMatrixCopy),19);
    MyShapeMatrixCopy[1][1]=1;
    QCOMPARE(myCppAlgo.getNumberOfFreecells(MyShapeMatrixCopy),18);
}

void TestmyApp::cppalgo_test_updateMatrixOccupency()
{
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    QCOMPARE(myCppAlgo.getNumberOfFreecells(MyShapeMatrixCopy),20);

    QVector<QVector<int>> nodeListTemp;
    myCppAlgo.clearAllNode(nodeListTemp);
    myCppAlgo.addNode(nodeListTemp,0, 0);
    myCppAlgo.updateMatrixOccupency(MyShapeMatrixCopy, nodeListTemp);
    QCOMPARE(myCppAlgo.getNumberOfFreecells(MyShapeMatrixCopy),19);
    myCppAlgo.addNode(nodeListTemp,1, 1);
    myCppAlgo.updateMatrixOccupency(MyShapeMatrixCopy, nodeListTemp);
    QCOMPARE(myCppAlgo.getNumberOfFreecells(MyShapeMatrixCopy),18);

}

void TestmyApp::cppalgo_test_getLongestLine()
{
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);
    QCOMPARE(myCppAlgo.getLongestLine(MyShapeMatrixCopy),5);

     QVector<QVector<int>> nodeListTemp;
    myCppAlgo.addNode(nodeListTemp,0, 2);
    myCppAlgo.addNode(nodeListTemp,1, 2);
    myCppAlgo.addNode(nodeListTemp,2, 2);
    myCppAlgo.addNode(nodeListTemp,3, 2);
    myCppAlgo.addNode(nodeListTemp,3, 0);
    myCppAlgo.addNode(nodeListTemp,3, 1);
    myCppAlgo.addNode(nodeListTemp,3, 2);
    myCppAlgo.addNode(nodeListTemp,3, 3);
    myCppAlgo.addNode(nodeListTemp,3, 4);
    myCppAlgo.updateMatrixOccupency(MyShapeMatrixCopy, nodeListTemp);
    QCOMPARE(myCppAlgo.getLongestLine(MyShapeMatrixCopy),3);


}

void TestmyApp::cppalgo_test_findTotalCostH(){

    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);

    QCOMPARE(myCppAlgo.findCostH(MyShapeMatrixCopy),6);
}

void TestmyApp::cppalgo_test_findTotalCostF(){
    QVector<QVector<int>> nodeListTemp;
    QVector<QVector<double>> MyShapeMatrixCopy;
    myShape.getMyShapeMatrixCopy(MyShapeMatrixCopy);

    QCOMPARE(myCppAlgo.findTotalCostF(nodeListTemp,MyShapeMatrixCopy),6);

    myCppAlgo.addNode(nodeListTemp,0, 0);
    myCppAlgo.updateMatrixOccupency(MyShapeMatrixCopy, nodeListTemp);
    QCOMPARE(myCppAlgo.findTotalCostF(nodeListTemp,MyShapeMatrixCopy),5);


}

QTEST_APPLESS_MAIN(TestmyApp)

#include "tst_testmyapp.moc"

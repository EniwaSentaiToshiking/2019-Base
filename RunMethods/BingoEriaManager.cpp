#include <iostream>
#include <string>
#define STR(var) #var

enum ColorID
{
    red = 0,
    blue = 1,
    yellow = 2,
    green = 3,
    black = 4,
};

enum NumberID
{
    one = 0,
    two = 1,
    three = 2,
    four = 3,
    five = 4,
    six = 5,
    seven = 6,
    eight = 7,

};

// エッジ
struct Edge
{
    /* Edge */
    // cost
    // このエッジを通るコスト 1 or 100
    // direction_id
    // 12時の方向 0
    // 3時の方向 1
    // 6時の方向 2
    // 9時の方向 3
    int directionId;
    int cost;
    bool is_exit;
    std::string name;
};

// ノード
struct Node
{
    /* Node */
    // positionは交点サークルの場所
    // is_placedはブロックが置かれているかどうか
    int nodeId;
    bool isPlaced;
    Edge edges[4];
    std::string name;
};

// ゴール候補
struct GoalCandidate
{
    /* GoalCandidate */
    Node node;
    int effectiveRouteCost;
    std::string name;
};

// ゴール
struct Goal
{
    /* Goal */
    Node node;
    GoalCandidate goalCandidate[2];
    std::string name;
};

// ブロックサークル
struct BlockBingoCircle
{
    /* data */
    NumberID numberId;
    ColorID colorId;
    Goal goal;
    std::string name;
};

// 作成する仮想ビンゴエリア
struct BingoEria
{
    /* data */
    Node node[16];
    BlockBingoCircle blockBingoCircle[8];
};

enum CourseType
{
    left = 0,
    right = 1,
};

void edgePrint(Edge edge)
{
    printf("edge.name: %s ", edge.name.c_str());
    printf("edge.directionId: %d ", edge.directionId);
    printf("edge.cost: %d ", edge.cost);
    printf("edge.is_exit: %d ", edge.is_exit);
};

void nodePrint(Node node)
{
    printf("node.name: %s ", node.name.c_str());
    printf("node.directionId: %d ", node.nodeId);
    printf("node.isPlaced: %d ", node.isPlaced);
    printf("\n");
    for (int i = 0; i < 4; i++)
    {
        printf("index %d ", i);
        edgePrint(node.edges[i]);
        printf("\n");
    }
}

void goalCandidatePrint(GoalCandidate goalCandidate)
{
    printf("goalCandidate.name: %s ", goalCandidate.name.c_str());
    nodePrint(goalCandidate.node);
    printf("goalCandidate.effectiveRouteCost: %d ", goalCandidate.effectiveRouteCost);
    printf("\n");
};

void goalPrint(Goal goal)
{
    printf("goal.name: %s ", goal.name.c_str());
    nodePrint(goal.node);
    printf("\n");
    for (int i = 0; i < 2; i++)
    {
        printf("index %d ", i);
        goalCandidatePrint(goal.goalCandidate[i]);
        printf("\n");
    }
};

void blockBingoCirclePrint(BlockBingoCircle blockBingoCircle)
{
    printf("blockBingoCircle.name: %s ", blockBingoCircle.name.c_str());
    printf("numberId: %d ", blockBingoCircle.numberId);
    printf("colorId: %d ", blockBingoCircle.colorId);
    printf("\n");
    goalPrint(blockBingoCircle.goal);
};

void BingoEriaPrint(BingoEria bingoEria)
{
    for (int i = 0; i < 16; i++)
    {
        printf("index %d ", i);
        nodePrint(bingoEria.node[i]);
        printf("\n");
    }

    for (int i = 0; i < 8; i++)
    {
        printf("index %d ", i);
        blockBingoCirclePrint(bingoEria.blockBingoCircle[i]);
        printf("\n");
    }
};

Edge initializeEdge(Edge edge, int directionId, int cost, bool is_exit, std::string name)
{
    edge.directionId = directionId;
    edge.cost = cost;
    edge.is_exit = is_exit;
    edge.name = name;
    return edge;
};

Node initializeNode(Node node, int nodeId, bool isPlaced, Edge edge00_0, Edge edge00_1, Edge edge00_2, Edge edge00_3, std::string name)
{
    node.nodeId = nodeId;
    node.isPlaced = isPlaced;
    node.edges[0] = edge00_0;
    node.edges[1] = edge00_1;
    node.edges[2] = edge00_2;
    node.edges[3] = edge00_3;
    node.name = name;
    return node;
};

GoalCandidate initialzeGoalCandidate(GoalCandidate goalCandidate, Node node, int effectiveRouteCost, std::string name)
{
    goalCandidate.node = node;
    goalCandidate.effectiveRouteCost = effectiveRouteCost;
    goalCandidate.name = name;
    return goalCandidate;
};

Goal initializeGoal(Goal goal, Node node, GoalCandidate goalCandidate1, GoalCandidate goalCandidate2, std::string name)
{
    goal.node = node;
    goal.goalCandidate[0] = goalCandidate1;
    goal.goalCandidate[1] = goalCandidate2;
    goal.name = name;
    return goal;
};

BlockBingoCircle initializeblockBingoCircle(BlockBingoCircle blockBingoCircle, NumberID numberId, ColorID colorId, Goal goal, std::string name)
{
    blockBingoCircle.numberId = numberId;
    blockBingoCircle.colorId = colorId;
    blockBingoCircle.goal = goal;
    blockBingoCircle.name = name;
    return blockBingoCircle;
}

BingoEria initializeBingoEria(BingoEria bingoEria,
                              Node node00, Node node01, Node node02, Node node03,
                              Node node10, Node node11, Node node12, Node node13,
                              Node node20, Node node21, Node node22, Node node23,
                              Node node30, Node node31, Node node32, Node node33,
                              BlockBingoCircle blockBingoCircle1, BlockBingoCircle blockBingoCircle2, BlockBingoCircle blockBingoCircle3, BlockBingoCircle blockBingoCircle4,
                              BlockBingoCircle blockBingoCircle5, BlockBingoCircle blockBingoCircle6, BlockBingoCircle blockBingoCircle7, BlockBingoCircle blockBingoCircle8)
{
    bingoEria.node[0] = node00;
    bingoEria.node[1] = node01;
    bingoEria.node[2] = node02;
    bingoEria.node[3] = node03;
    bingoEria.node[4] = node10;
    bingoEria.node[5] = node11;
    bingoEria.node[6] = node12;
    bingoEria.node[7] = node13;
    bingoEria.node[8] = node20;
    bingoEria.node[9] = node21;
    bingoEria.node[10] = node22;
    bingoEria.node[11] = node23;
    bingoEria.node[12] = node30;
    bingoEria.node[13] = node31;
    bingoEria.node[14] = node32;
    bingoEria.node[15] = node33;

    bingoEria.blockBingoCircle[0] = blockBingoCircle1;
    bingoEria.blockBingoCircle[1] = blockBingoCircle2;
    bingoEria.blockBingoCircle[2] = blockBingoCircle3;
    bingoEria.blockBingoCircle[3] = blockBingoCircle4;
    bingoEria.blockBingoCircle[4] = blockBingoCircle5;
    bingoEria.blockBingoCircle[5] = blockBingoCircle6;
    bingoEria.blockBingoCircle[6] = blockBingoCircle7;
    bingoEria.blockBingoCircle[7] = blockBingoCircle8;

    return bingoEria;
}

class Hoge
{
public:
    // Hoge();
    Hoge(CourseType courseType);
    // 1行目
    Edge edge00_0;
    Edge edge00_1;
    Edge edge00_2;
    Edge edge00_3;

    Edge edge01_0;
    Edge edge01_1;
    Edge edge01_2;
    Edge edge01_3;

    Edge edge02_0;
    Edge edge02_1;
    Edge edge02_2;
    Edge edge02_3;

    Edge edge03_0;
    Edge edge03_1;
    Edge edge03_2;
    Edge edge03_3;

    // 2行目
    Edge edge10_0;
    Edge edge10_1;
    Edge edge10_2;
    Edge edge10_3;

    Edge edge11_0;
    Edge edge11_1;
    Edge edge11_2;
    Edge edge11_3;

    Edge edge12_0;
    Edge edge12_1;
    Edge edge12_2;
    Edge edge12_3;

    Edge edge13_0;
    Edge edge13_1;
    Edge edge13_2;
    Edge edge13_3;

    // 3行目
    Edge edge20_0;
    Edge edge20_1;
    Edge edge20_2;
    Edge edge20_3;

    Edge edge21_0;
    Edge edge21_1;
    Edge edge21_2;
    Edge edge21_3;

    Edge edge22_0;
    Edge edge22_1;
    Edge edge22_2;
    Edge edge22_3;

    Edge edge23_0;
    Edge edge23_1;
    Edge edge23_2;
    Edge edge23_3;

    // 4行目
    Edge edge30_0;
    Edge edge30_1;
    Edge edge30_2;
    Edge edge30_3;

    Edge edge31_0;
    Edge edge31_1;
    Edge edge31_2;
    Edge edge31_3;

    Edge edge32_0;
    Edge edge32_1;
    Edge edge32_2;
    Edge edge32_3;

    Edge edge33_0;
    Edge edge33_1;
    Edge edge33_2;
    Edge edge33_3;

    // 1行目
    Node node00;
    Node node01;
    Node node02;
    Node node03;
    // 2行目
    Node node10;
    Node node11;
    Node node12;
    Node node13;
    // 3行目
    Node node20;
    Node node21;
    Node node22;
    Node node23;
    // 4行目
    Node node30;
    Node node31;
    Node node32;
    Node node33;

    // ゴール候補
    GoalCandidate goalCandidate1_1;
    GoalCandidate goalCandidate1_2;

    GoalCandidate goalCandidate2_1;
    GoalCandidate goalCandidate2_2;

    GoalCandidate goalCandidate3_1;
    GoalCandidate goalCandidate3_2;

    GoalCandidate goalCandidate4_1;
    GoalCandidate goalCandidate4_2;

    GoalCandidate goalCandidate5_1;
    GoalCandidate goalCandidate5_2;

    GoalCandidate goalCandidate6_1;
    GoalCandidate goalCandidate6_2;

    GoalCandidate goalCandidate7_1;
    GoalCandidate goalCandidate7_2;

    GoalCandidate goalCandidate8_1;
    GoalCandidate goalCandidate8_2;

    // ブロックビンゴ
    Goal goal1;
    Goal goal2;
    Goal goal3;
    Goal goal4;
    Goal goal5;
    Goal goal6;
    Goal goal7;
    Goal goal8;

    // ブロックビンゴサークル
    BlockBingoCircle blockBingoCircle1;
    BlockBingoCircle blockBingoCircle2;
    BlockBingoCircle blockBingoCircle3;
    BlockBingoCircle blockBingoCircle4;
    BlockBingoCircle blockBingoCircle5;
    BlockBingoCircle blockBingoCircle6;
    BlockBingoCircle blockBingoCircle7;
    BlockBingoCircle blockBingoCircle8;

    // 仮想ビンゴエリア
    BingoEria bingoEria;
};

Hoge::Hoge(CourseType courseType)
{
    // 1行目
    edge00_0 = initializeEdge(edge00_0, 0, 100, false, "edge00_0");
    edge00_1 = initializeEdge(edge00_1, 1, 1, true, "edge00_1");
    edge00_2 = initializeEdge(edge00_2, 2, 1, true, "edge00_2");
    edge00_3 = initializeEdge(edge00_3, 3, 100, false, "edge00_3");

    edge01_0 = initializeEdge(edge01_0, 0, 100, false, "edge01_0");
    edge01_1 = initializeEdge(edge01_1, 1, 1, true, "edge01_1");
    edge01_2 = initializeEdge(edge01_2, 2, 1, true, "edge01_2");
    edge01_3 = initializeEdge(edge01_3, 3, 1, true, "edge01_3");

    edge02_0 = initializeEdge(edge02_0, 0, 100, false, "edge02_0");
    edge02_1 = initializeEdge(edge02_1, 1, 1, true, "edge02_1");
    edge02_2 = initializeEdge(edge02_2, 2, 1, true, "edge02_2");
    edge02_3 = initializeEdge(edge02_3, 3, 1, true, "edge02_3");

    edge03_0 = initializeEdge(edge03_0, 0, 100, false, "edge03_0");
    edge03_1 = initializeEdge(edge03_0, 1, 1, true, "edge03_1");
    edge03_2 = initializeEdge(edge03_0, 2, 100, false, "edge03_2");
    edge03_3 = initializeEdge(edge03_0, 3, 1, true, "edge03_3");

    // 2行目
    edge10_0 = initializeEdge(edge10_0, 0, 1, true, "edge10_0");
    edge10_1 = initializeEdge(edge10_1, 1, 1, true, "edge10_1");
    edge10_2 = initializeEdge(edge10_2, 2, 1, true, "edge10_2");
    edge10_3 = initializeEdge(edge10_3, 3, 100, false, "edge10_3");

    edge11_0 = initializeEdge(edge11_0, 0, 1, true, "edge11_0");
    edge11_1 = initializeEdge(edge11_1, 1, 1, true, "edge11_1");
    edge11_2 = initializeEdge(edge11_2, 2, 1, true, "edge11_2");
    edge11_3 = initializeEdge(edge11_3, 3, 1, true, "edge11_3");

    edge12_0 = initializeEdge(edge12_0, 0, 1, true, "edge12_0");
    edge12_1 = initializeEdge(edge12_1, 1, 1, true, "edge12_1");
    edge12_2 = initializeEdge(edge12_2, 2, 1, true, "edge12_2");
    edge12_3 = initializeEdge(edge12_3, 3, 1, true, "edge12_3");

    // 3行目
    edge20_0 = initializeEdge(edge20_0, 0, 1, true, "edge20_0");
    edge20_1 = initializeEdge(edge20_1, 1, 1, true, "edge20_1");
    edge20_2 = initializeEdge(edge20_2, 2, 1, true, "edge20_2");
    edge20_3 = initializeEdge(edge20_2, 3, 100, false, "edge20_3");

    edge21_0 = initializeEdge(edge21_0, 0, 1, true, "edge21_0");
    edge21_1 = initializeEdge(edge21_1, 1, 1, true, "edge21_1");
    edge21_2 = initializeEdge(edge21_2, 2, 1, true, "edge21_2");
    edge21_3 = initializeEdge(edge21_3, 3, 1, true, "edge21_3");

    edge22_0 = initializeEdge(edge22_0, 0, 1, true, "edge22_0");
    edge22_1 = initializeEdge(edge22_1, 1, 1, true, "edge22_1");
    edge22_2 = initializeEdge(edge22_2, 2, 1, true, "edge22_2");
    edge22_3 = initializeEdge(edge22_3, 3, 1, true, "edge22_3");

    edge23_0 = initializeEdge(edge23_0, 0, 1, true, "edge23_0");
    edge23_1 = initializeEdge(edge23_1, 1, 100, false, "edge23_1");
    edge23_2 = initializeEdge(edge23_2, 2, 1, true, "edge23_2");
    edge23_3 = initializeEdge(edge23_3, 3, 1, true, "edge23_3");

    // 4行目
    edge30_0 = initializeEdge(edge30_0, 0, 1, true, "edge30_0");
    edge30_1 = initializeEdge(edge30_1, 1, 1, true, "edge30_1");
    edge30_2 = initializeEdge(edge30_2, 2, 100, false, "edge30_2");
    edge30_3 = initializeEdge(edge30_3, 3, 100, false, "edge30_3");

    edge31_0 = initializeEdge(edge31_0, 0, 1, true, "edge31_0");
    edge31_1 = initializeEdge(edge31_1, 1, 1, true, "edge31_1");
    edge31_2 = initializeEdge(edge31_1, 2, 100, false, "edge31_2");
    edge31_3 = initializeEdge(edge31_1, 3, 1, true, "edge31_3");

    edge32_0 = initializeEdge(edge32_0, 0, 1, true, "edge32_0");
    edge32_1 = initializeEdge(edge32_1, 1, 1, true, "edge32_1");
    edge32_2 = initializeEdge(edge32_2, 2, 100, false, "edge32_2");
    edge32_3 = initializeEdge(edge32_3, 3, 1, true, "edge32_3");

    edge33_0 = initializeEdge(edge33_0, 0, 1, true, "edge33_0");
    edge33_1 = initializeEdge(edge33_1, 1, 100, false, "edge33_1");
    edge33_2 = initializeEdge(edge33_2, 2, 100, false, "edge33_2");
    edge33_3 = initializeEdge(edge33_3, 3, 1, true, "edge33_3");

    // 1行目
    node00 = initializeNode(node00, 0, false, edge00_0, edge00_1, edge00_2, edge00_3, "node00");
    node01 = initializeNode(node01, 0, false, edge01_0, edge01_1, edge01_2, edge01_3, "node01");
    node02 = initializeNode(node02, 0, false, edge02_0, edge02_1, edge02_2, edge02_3, "node02");
    node03 = initializeNode(node03, 0, false, edge03_0, edge03_1, edge03_2, edge03_3, "node03");

    // 2行目
    node10 = initializeNode(node10, 0, false, edge10_0, edge10_1, edge10_2, edge10_3, "node10");
    node11 = initializeNode(node11, 0, false, edge11_0, edge11_1, edge11_2, edge11_3, "node11");
    node12 = initializeNode(node12, 0, false, edge12_0, edge12_1, edge12_2, edge12_3, "node12");
    node32 = initializeNode(node32, 0, false, edge32_0, edge32_1, edge32_2, edge32_3, "node32");

    // 3行目
    node20 = initializeNode(node20, 0, false, edge20_0, edge20_1, edge20_2, edge20_3, "node20");
    node21 = initializeNode(node21, 0, false, edge21_0, edge21_1, edge21_2, edge21_3, "node21");
    node22 = initializeNode(node22, 0, false, edge22_0, edge22_1, edge22_2, edge22_3, "node22");
    node23 = initializeNode(node23, 0, false, edge23_0, edge23_1, edge23_2, edge23_3, "node23");

    // 4行目
    node30 = initializeNode(node30, 0, false, edge30_0, edge30_1, edge30_2, edge30_3, "node30");
    node31 = initializeNode(node31, 0, false, edge31_0, edge31_1, edge31_2, edge31_3, "node31");
    node32 = initializeNode(node32, 0, false, edge32_0, edge32_1, edge32_2, edge32_3, "node32");
    node33 = initializeNode(node33, 0, false, edge33_0, edge33_1, edge33_2, edge33_3, "node33");

    // ゴール候補
    goalCandidate1_1 = initialzeGoalCandidate(goalCandidate1_1, node00, 100, "goalCandidate1");
    goalCandidate1_2 = initialzeGoalCandidate(goalCandidate1_2, node00, 100, "goalCandidate2");

    goalCandidate2_1 = initialzeGoalCandidate(goalCandidate2_1, node00, 100, "goalCandidate1");
    goalCandidate2_2 = initialzeGoalCandidate(goalCandidate2_2, node00, 100, "goalCandidate2");

    goalCandidate3_1 = initialzeGoalCandidate(goalCandidate3_1, node00, 100, "goalCandidate1");
    goalCandidate3_2 = initialzeGoalCandidate(goalCandidate3_2, node00, 100, "goalCandidate2");

    goalCandidate4_1 = initialzeGoalCandidate(goalCandidate4_1, node00, 100, "goalCandidate1");
    goalCandidate4_2 = initialzeGoalCandidate(goalCandidate4_2, node00, 100, "goalCandidate2");

    goalCandidate5_1 = initialzeGoalCandidate(goalCandidate5_1, node00, 100, "goalCandidate1");
    goalCandidate5_2 = initialzeGoalCandidate(goalCandidate5_2, node00, 100, "goalCandidate2");

    goalCandidate6_1 = initialzeGoalCandidate(goalCandidate6_1, node00, 100, "goalCandidate1");
    goalCandidate6_2 = initialzeGoalCandidate(goalCandidate7_1, node00, 100, "goalCandidate2");

    goalCandidate7_1 = initialzeGoalCandidate(goalCandidate7_1, node00, 100, "goalCandidate1");
    goalCandidate7_2 = initialzeGoalCandidate(goalCandidate7_2, node00, 100, "goalCandidate2");

    goalCandidate8_1 = initialzeGoalCandidate(goalCandidate8_1, node00, 100, "goalCandidate1");
    goalCandidate8_2 = initialzeGoalCandidate(goalCandidate8_2, node00, 100, "goalCandidate2");

    // ブロックビンゴサークルに対するゴール node00, goalCandidate1_1, goalCandidate1_2はただの初期値
    goal1 = initializeGoal(goal1, node00, goalCandidate1_1, goalCandidate1_2, "goal1");
    goal2 = initializeGoal(goal2, node00, goalCandidate2_1, goalCandidate2_2, "goal2");
    goal3 = initializeGoal(goal3, node00, goalCandidate3_1, goalCandidate3_2, "goal3");
    goal4 = initializeGoal(goal4, node00, goalCandidate4_1, goalCandidate4_2, "goal4");
    goal5 = initializeGoal(goal5, node00, goalCandidate5_1, goalCandidate5_2, "goal5");
    goal6 = initializeGoal(goal6, node00, goalCandidate6_1, goalCandidate6_2, "goal6");
    goal7 = initializeGoal(goal7, node00, goalCandidate7_1, goalCandidate7_2, "goal7");
    goal8 = initializeGoal(goal8, node00, goalCandidate8_1, goalCandidate8_2, "goal8");

    // ブロックビンゴサークル
    blockBingoCircle1 = initializeblockBingoCircle(blockBingoCircle1, one, red, goal1, "blockBingoCircle1");
    blockBingoCircle2 = initializeblockBingoCircle(blockBingoCircle2, two, red, goal2, "blockBingoCircle2");
    blockBingoCircle3 = initializeblockBingoCircle(blockBingoCircle3, three, red, goal3, "blockBingoCircle3");
    blockBingoCircle4 = initializeblockBingoCircle(blockBingoCircle4, four, red, goal4, "blockBingoCircle4");
    blockBingoCircle5 = initializeblockBingoCircle(blockBingoCircle5, five, red, goal5, "blockBingoCircle5");
    blockBingoCircle6 = initializeblockBingoCircle(blockBingoCircle6, six, red, goal6, "blockBingoCircle6");
    blockBingoCircle7 = initializeblockBingoCircle(blockBingoCircle7, seven, red, goal7, "blockBingoCircle7");
    blockBingoCircle8 = initializeblockBingoCircle(blockBingoCircle8, eight, red, goal8, "blockBingoCircle8");

    switch (courseType)
    {
    case right:
        goalCandidate1_1.node = node01;
        goalCandidate1_2.node = node11;
        goal1.goalCandidate[0] = goalCandidate1_1;
        goal1.goalCandidate[1] = goalCandidate1_2;
        blockBingoCircle1.colorId = red;

        goalCandidate2_1.node = node02;
        goalCandidate2_2.node = node12;
        goal2.goalCandidate[0] = goalCandidate2_1;
        goal2.goalCandidate[1] = goalCandidate2_2;
        blockBingoCircle2.colorId = green;

        goalCandidate3_1.node = node03;
        goalCandidate3_2.node = node13;
        goal3.goalCandidate[0] = goalCandidate3_1;
        goal3.goalCandidate[1] = goalCandidate3_2;
        blockBingoCircle3.colorId = yellow;

        goalCandidate4_1.node = node11;
        goalCandidate4_2.node = node21;
        goal4.goalCandidate[0] = goalCandidate4_1;
        goal4.goalCandidate[1] = goalCandidate4_2;
        blockBingoCircle4.colorId = yellow;

        goalCandidate5_1.node = node13;
        goalCandidate5_2.node = node23;
        goal5.goalCandidate[0] = goalCandidate5_1;
        goal5.goalCandidate[1] = goalCandidate5_2;
        blockBingoCircle5.colorId = blue;

        goalCandidate6_1.node = node21;
        goalCandidate6_2.node = node31;
        goal6.goalCandidate[0] = goalCandidate6_1;
        goal6.goalCandidate[1] = goalCandidate6_2;
        blockBingoCircle6.colorId = blue;

        goalCandidate7_1.node = node22;
        goalCandidate7_2.node = node32;
        goal7.goalCandidate[0] = goalCandidate7_1;
        goal7.goalCandidate[1] = goalCandidate7_2;
        blockBingoCircle7.colorId = red;

        goalCandidate8_1.node = node23;
        goalCandidate8_2.node = node33;
        goal8.goalCandidate[0] = goalCandidate8_1;
        goal8.goalCandidate[1] = goalCandidate8_2;
        blockBingoCircle8.colorId = green;
        break;
    case left:
        goalCandidate1_1.node = node00;
        goalCandidate1_2.node = node10;
        goal1.goalCandidate[0] = goalCandidate1_1;
        goal1.goalCandidate[1] = goalCandidate1_2;
        blockBingoCircle1.colorId = yellow;

        goalCandidate2_1.node = node01;
        goalCandidate2_2.node = node11;
        goal2.goalCandidate[0] = goalCandidate2_1;
        goal2.goalCandidate[1] = goalCandidate2_2;
        blockBingoCircle2.colorId = green;

        goalCandidate3_1.node = node02;
        goalCandidate3_2.node = node12;
        goal3.goalCandidate[0] = goalCandidate3_1;
        goal3.goalCandidate[1] = goalCandidate3_2;
        blockBingoCircle3.colorId = red;

        goalCandidate4_1.node = node10;
        goalCandidate4_2.node = node20;
        goal4.goalCandidate[0] = goalCandidate4_1;
        goal4.goalCandidate[1] = goalCandidate4_2;
        blockBingoCircle4.colorId = blue;

        goalCandidate5_1.node = node12;
        goalCandidate5_2.node = node22;
        goal5.goalCandidate[0] = goalCandidate5_1;
        goal5.goalCandidate[1] = goalCandidate5_2;
        blockBingoCircle4.colorId = yellow;

        goalCandidate6_1.node = node20;
        goalCandidate6_2.node = node30;
        goal6.goalCandidate[0] = goalCandidate6_1;
        goal6.goalCandidate[1] = goalCandidate6_2;
        blockBingoCircle6.colorId = green;

        goalCandidate7_1.node = node21;
        goalCandidate7_2.node = node31;
        goal7.goalCandidate[0] = goalCandidate7_1;
        goal7.goalCandidate[1] = goalCandidate7_2;
        blockBingoCircle7.colorId = red;

        goalCandidate8_1.node = node22;
        goalCandidate8_2.node = node32;
        goal8.goalCandidate[0] = goalCandidate8_1;
        goal8.goalCandidate[1] = goalCandidate8_2;
        blockBingoCircle8.colorId = blue;
        break;
    }

    bingoEria = initializeBingoEria(bingoEria,
                                    node00, node01, node02, node03,
                                    node10, node11, node12, node13,
                                    node20, node21, node22, node23,
                                    node30, node31, node32, node33,
                                    blockBingoCircle1, blockBingoCircle2, blockBingoCircle3, blockBingoCircle4,
                                    blockBingoCircle5, blockBingoCircle6, blockBingoCircle7, blockBingoCircle8);
}

int main()
{
    CourseType courseType = right;
    Hoge h = Hoge(courseType);
    BingoEriaPrint(h.bingoEria);
    // // 1行目
    // Edge edge00_0 = {0, 1, false, "edge00_0"};
    // Edge edge00_1 = {1, 1, true, "edge00_1"};
    // Edge edge00_2 = {2, 1, true, "edge00_2"};
    // Edge edge00_3 = {3, 1, false, "edge00_3"};

    // Edge edge01_0 = {0, 1, false, "edge01_0"};
    // Edge edge01_1 = {1, 1, true, "edge01_1"};
    // Edge edge01_2 = {2, 1, true, "edge01_2"};
    // Edge edge01_3 = {3, 1, true, "edge01_3"};

    // Edge edge02_0 = {0, 1, false, "edge02_0"};
    // Edge edge02_1 = {1, 1, true, "edge02_1"};
    // Edge edge02_2 = {2, 1, true, "edge02_2"};
    // Edge edge02_3 = {3, 1, true, "edge02_3"};

    // Edge edge03_0 = {0, 1, false, "edge03_0"};
    // Edge edge03_1 = {1, 1, true, "edge03_1"};
    // Edge edge03_2 = {2, 1, false, "edge03_2"};
    // Edge edge03_3 = {3, 1, true, "edge03_3"};

    // // 2行目
    // Edge edge10_0 = {0, 1, true, "edge10_0"};
    // Edge edge10_1 = {1, 1, true, "edge10_1"};
    // Edge edge10_2 = {2, 1, true, "edge10_2"};
    // Edge edge10_3 = {3, 1, false, "edge10_3"};

    // Edge edge11_0 = {0, 1, true, "edge11_0"};
    // Edge edge11_1 = {1, 1, true, "edge11_1"};
    // Edge edge11_2 = {2, 1, true, "edge11_2"};
    // Edge edge11_3 = {3, 1, true, "edge11_3"};

    // Edge edge12_0 = {0, 1, true, "edge12_0"};
    // Edge edge12_1 = {1, 1, true, "edge12_1"};
    // Edge edge12_2 = {2, 1, true, "edge12_2"};
    // Edge edge12_3 = {3, 1, true, "edge12_3"};

    // Edge edge13_0 = {0, 1, true, "edge13_0"};
    // Edge edge13_1 = {1, 1, false, "edge13_1"};
    // Edge edge13_2 = {2, 1, true, "edge13_2"};
    // Edge edge13_3 = {3, 1, true, "edge13_3"};

    // // 3行目
    // Edge edge20_0 = {0, 1, true, "edge20_0"};
    // Edge edge20_1 = {1, 1, true, "edge20_1"};
    // Edge edge20_2 = {2, 1, true, "edge20_2"};
    // Edge edge20_3 = {3, 1, false, "edge20_3"};

    // Edge edge21_0 = {0, 1, true, "edge21_0"};
    // Edge edge21_1 = {1, 1, true, "edge21_1"};
    // Edge edge21_2 = {2, 1, true, "edge21_2"};
    // Edge edge21_3 = {3, 1, true, "edge21_3"};

    // Edge edge22_0 = {0, 1, true, "edge22_0"};
    // Edge edge22_1 = {1, 1, true, "edge22_1"};
    // Edge edge22_2 = {2, 1, true, "edge22_2"};
    // Edge edge22_3 = {3, 1, true, "edge22_3"};

    // Edge edge23_0 = {0, 1, true, "edge23_0"};
    // Edge edge23_1 = {1, 1, false, "edge23_1"};
    // Edge edge23_2 = {2, 1, true, "edge23_2"};
    // Edge edge23_3 = {3, 1, true, "edge23_3"};

    // // 4行目
    // Edge edge30_0 = {0, 1, true, "edge30_0"};
    // Edge edge30_1 = {1, 1, true, "edge30_1"};
    // Edge edge30_2 = {2, 1, false, "edge30_2"};
    // Edge edge30_3 = {3, 1, false, "edge30_3"};

    // Edge edge31_0 = {0, 1, true, "edge31_0"};
    // Edge edge31_1 = {1, 1, true, "edge31_1"};
    // Edge edge31_2 = {2, 1, false, "edge31_2"};
    // Edge edge31_3 = {3, 1, true, "edge31_3"};

    // Edge edge32_0 = {0, 1, true, "edge32_0"};
    // Edge edge32_1 = {1, 1, true, "edge32_1"};
    // Edge edge32_2 = {2, 1, false, "edge32_2"};
    // Edge edge32_3 = {3, 1, true, "edge32_3"};

    // Edge edge33_0 = {0, 1, true, "edge33_0"};
    // Edge edge33_1 = {1, 1, false, "edge33_1"};
    // Edge edge33_2 = {2, 1, false, "edge33_2"};
    // Edge edge33_3 = {3, 1, true, "edge33_3"};

    // // 1行目
    // Node node00 = {0, false, {edge00_0, edge00_1, edge00_2, edge00_3}, "node00"};
    // Node node01 = {0, false, {edge01_0, edge01_1, edge01_2, edge01_3}, "node01"};
    // Node node02 = {0, false, {edge02_0, edge02_1, edge02_2, edge02_3}, "node02"};
    // Node node03 = {0, false, {edge03_0, edge03_1, edge03_2, edge03_3}, "node03"};

    // // 2行目
    // Node node10 = {0, false, {edge10_0, edge10_1, edge10_2, edge10_3}, "node10"};
    // Node node11 = {0, false, {edge11_0, edge11_1, edge11_2, edge11_3}, "node11"};
    // Node node12 = {0, false, {edge12_0, edge12_1, edge12_2, edge12_3}, "node12"};
    // Node node13 = {0, false, {edge13_0, edge13_1, edge13_2, edge13_3}, "node13"};

    // // 3行目
    // Node node20 = {0, false, {edge20_0, edge20_1, edge20_2, edge20_3}, "node20"};
    // Node node21 = {0, false, {edge21_0, edge21_1, edge21_2, edge21_3}, "node21"};
    // Node node22 = {0, false, {edge22_0, edge22_1, edge22_2, edge22_3}, "node22"};
    // Node node23 = {0, false, {edge23_0, edge23_1, edge23_2, edge23_3}, "node23"};

    // // 4行目
    // Node node30 = {0, false, {edge30_0, edge30_1, edge30_2, edge30_3}, "node30"};
    // Node node31 = {0, false, {edge31_0, edge31_1, edge31_2, edge31_3}, "node31"};
    // Node node32 = {0, false, {edge32_0, edge32_1, edge32_2, edge32_3}, "node32"};
    // Node node33 = {0, false, {edge33_0, edge33_1, edge33_2, edge33_3}, "node33"};

    // Node nodes[] = {node00, node01, node02, node03, node10, node11, node12, node13, node20, node21, node22, node23, node30, node31, node32, node33};

    // // ゴール候補
    // GoalCandidate goalCandidate1_1 = {node00, 100, "goalCandidate1"};
    // GoalCandidate goalCandidate1_2 = {node00, 100, "goalCandidate2"};

    // GoalCandidate goalCandidate2_1 = {node00, 100, "goalCandidate1"};
    // GoalCandidate goalCandidate2_2 = {node00, 100, "goalCandidate2"};

    // GoalCandidate goalCandidate3_1 = {node00, 100, "goalCandidate1"};
    // GoalCandidate goalCandidate3_2 = {node00, 100, "goalCandidate2"};

    // GoalCandidate goalCandidate4_1 = {node00, 100, "goalCandidate1"};
    // GoalCandidate goalCandidate4_2 = {node00, 100, "goalCandidate2"};

    // GoalCandidate goalCandidate5_1 = {node00, 100, "goalCandidate1"};
    // GoalCandidate goalCandidate5_2 = {node00, 100, "goalCandidate2"};

    // GoalCandidate goalCandidate6_1 = {node00, 100, "goalCandidate1"};
    // GoalCandidate goalCandidate6_2 = {node00, 100, "goalCandidate2"};

    // GoalCandidate goalCandidate7_1 = {node00, 100, "goalCandidate1"};
    // GoalCandidate goalCandidate7_2 = {node00, 100, "goalCandidate2"};

    // GoalCandidate goalCandidate8_1 = {node00, 100, "goalCandidate1"};
    // GoalCandidate goalCandidate8_2 = {node00, 100, "goalCandidate2"};

    // // ブロックビンゴサークルに対するゴール
    // Goal goal1 = {NULL, "goal1"};
    // Goal goal2 = {NULL, "goal2"};
    // Goal goal3 = {NULL, "goal3"};
    // Goal goal4 = {NULL, "goal4"};
    // Goal goal5 = {NULL, "goal5"};
    // Goal goal6 = {NULL, "goal6"};
    // Goal goal7 = {NULL, "goal7"};
    // Goal goal8 = {NULL, "goal8"};

    // // ブロックビンゴサークル
    // BlockBingoCircle blockBingoCircle1 = {one, red, goal1, "blockBingoCircle1"};
    // BlockBingoCircle blockBingoCircle2 = {two, red, goal2, "blockBingoCircle2"};
    // BlockBingoCircle blockBingoCircle3 = {three, red, goal3, "blockBingoCircle3"};
    // BlockBingoCircle blockBingoCircle4 = {four, red, goal4, "blockBingoCircle4"};
    // BlockBingoCircle blockBingoCircle5 = {five, red, goal5, "blockBingoCircle5"};
    // BlockBingoCircle blockBingoCircle6 = {six, red, goal6, "blockBingoCircle6"};
    // BlockBingoCircle blockBingoCircle7 = {seven, red, goal7, "blockBingoCircle7"};
    // BlockBingoCircle blockBingoCircle8 = {eight, red, goal8, "blockBingoCircle8"};

    // CourseType courseType = right;

    // switch (courseType)
    // {
    // case right:
    //     goalCandidate1_1.node = node01;
    //     goalCandidate1_2.node = node11;
    //     goal1.goalCandidate[0] = goalCandidate1_1;
    //     goal1.goalCandidate[1] = goalCandidate1_2;
    //     blockBingoCircle1.colorId = red;

    //     goalCandidate2_1.node = node02;
    //     goalCandidate2_2.node = node12;
    //     goal2.goalCandidate[0] = goalCandidate2_1;
    //     goal2.goalCandidate[1] = goalCandidate2_2;
    //     blockBingoCircle2.colorId = green;

    //     goalCandidate3_1.node = node03;
    //     goalCandidate3_2.node = node13;
    //     goal3.goalCandidate[0] = goalCandidate3_1;
    //     goal3.goalCandidate[1] = goalCandidate3_2;
    //     blockBingoCircle3.colorId = yellow;

    //     goalCandidate4_1.node = node11;
    //     goalCandidate4_2.node = node21;
    //     goal4.goalCandidate[0] = goalCandidate4_1;
    //     goal4.goalCandidate[1] = goalCandidate4_2;
    //     blockBingoCircle4.colorId = yellow;

    //     goalCandidate5_1.node = node13;
    //     goalCandidate5_2.node = node23;
    //     goal5.goalCandidate[0] = goalCandidate5_1;
    //     goal5.goalCandidate[1] = goalCandidate5_2;
    //     blockBingoCircle5.colorId = blue;

    //     goalCandidate6_1.node = node21;
    //     goalCandidate6_2.node = node31;
    //     goal6.goalCandidate[0] = goalCandidate6_1;
    //     goal6.goalCandidate[1] = goalCandidate6_2;
    //     blockBingoCircle6.colorId = blue;

    //     goalCandidate7_1.node = node22;
    //     goalCandidate7_2.node = node32;
    //     goal7.goalCandidate[0] = goalCandidate7_1;
    //     goal7.goalCandidate[1] = goalCandidate7_2;
    //     blockBingoCircle7.colorId = red;

    //     goalCandidate8_1.node = node23;
    //     goalCandidate8_2.node = node33;
    //     goal8.goalCandidate[0] = goalCandidate8_1;
    //     goal8.goalCandidate[1] = goalCandidate8_2;
    //     blockBingoCircle8.colorId = green;
    //     break;
    // case left:
    //     goalCandidate1_1.node = node00;
    //     goalCandidate1_2.node = node10;
    //     goal1.goalCandidate[0] = goalCandidate1_1;
    //     goal1.goalCandidate[1] = goalCandidate1_2;
    //     blockBingoCircle1.colorId = yellow;

    //     goalCandidate2_1.node = node01;
    //     goalCandidate2_2.node = node11;
    //     goal2.goalCandidate[0] = goalCandidate2_1;
    //     goal2.goalCandidate[1] = goalCandidate2_2;
    //     blockBingoCircle2.colorId = green;

    //     goalCandidate3_1.node = node02;
    //     goalCandidate3_2.node = node12;
    //     goal3.goalCandidate[0] = goalCandidate3_1;
    //     goal3.goalCandidate[1] = goalCandidate3_2;
    //     blockBingoCircle3.colorId = red;

    //     goalCandidate4_1.node = node10;
    //     goalCandidate4_2.node = node20;
    //     goal4.goalCandidate[0] = goalCandidate4_1;
    //     goal4.goalCandidate[1] = goalCandidate4_2;
    //     blockBingoCircle4.colorId = blue;

    //     goalCandidate5_1.node = node12;
    //     goalCandidate5_2.node = node22;
    //     goal5.goalCandidate[0] = goalCandidate5_1;
    //     goal5.goalCandidate[1] = goalCandidate5_2;
    //     blockBingoCircle4.colorId = yellow;

    //     goalCandidate6_1.node = node20;
    //     goalCandidate6_2.node = node30;
    //     goal6.goalCandidate[0] = goalCandidate6_1;
    //     goal6.goalCandidate[1] = goalCandidate6_2;
    //     blockBingoCircle6.colorId = green;

    //     goalCandidate7_1.node = node21;
    //     goalCandidate7_2.node = node31;
    //     goal7.goalCandidate[0] = goalCandidate7_1;
    //     goal7.goalCandidate[1] = goalCandidate7_2;
    //     blockBingoCircle7.colorId = red;

    //     goalCandidate8_1.node = node22;
    //     goalCandidate8_2.node = node32;
    //     goal8.goalCandidate[0] = goalCandidate8_1;
    //     goal8.goalCandidate[1] = goalCandidate8_2;
    //     blockBingoCircle8.colorId = blue;
    //     break;
    // }

    // BlockBingoCircle blockBingoCircles[] = {blockBingoCircle1, blockBingoCircle2, blockBingoCircle3, blockBingoCircle4, blockBingoCircle5, blockBingoCircle6, blockBingoCircle7, blockBingoCircle8};

    // // 仮想ブロックビンゴエリア
    // BingoEria bingoEria = {nodes, blockBingoCircles};
    // BingoEriaPrint(bingoEria);

    return 0;
}
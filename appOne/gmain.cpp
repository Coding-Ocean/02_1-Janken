#include"libOne.h"
void gmain(){
    window(800, 450);
    //�摜�ǂݍ���
    int playerGuImg = loadImage("assets\\playerGu.png");
    int playerChokiImg = loadImage("assets\\playerChoki.png");
    int playerPaImg = loadImage("assets\\playerPa.png");
    int pcGuImg = loadImage("assets\\pcGu.png");
    int pcChokiImg = loadImage("assets\\pcChoki.png");
    int pcPaImg = loadImage("assets\\pcPa.png");
    //��̔ԍ�
    const int GU = 0;
    const int CHOKI = 1;
    const int PA = 2;
    //�v���C���[�f�[�^
    int playerImg = playerGuImg;
    int playerHand = GU;
    float playerPx = 225;
    float playerPy = 225;
    float playerR = 255;
    float playerG = 255;
    float playerB = 255;
    //�o�b�f�[�^
    int pcImg = pcGuImg;
    int pcHand = GU;
    float pcPx = 575;
    float pcPy = 225;
    float pcR = 255;
    float pcG = 255;
    float pcB = 255;
    //���C�����[�v
    while (notQuit){
        //A,S,D�����ꂩ�̃L�[�������ꂽ��
        if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
            //�v���C���[�̎�����߂�
            if (isTrigger(KEY_A)) { playerHand = GU; }
            else if (isTrigger(KEY_S)) { playerHand = CHOKI; }
            else if (isTrigger(KEY_D)) { playerHand = PA; }
            //�v���C���[�̉摜��؂�ւ���
            if (playerHand == GU) { playerImg = playerGuImg; }
            else if (playerHand == CHOKI) { playerImg = playerChokiImg; }
            else if (playerHand == PA) { playerImg = playerPaImg; }
            //�o�b�̎�����߂�
            pcHand = random() % 3;
            //�o�b�̉摜��؂�ւ���
            if (pcHand == GU) { pcImg = pcGuImg; }
            else if (pcHand == CHOKI) { pcImg = pcChokiImg; }
            else if (pcHand == PA) { pcImg = pcPaImg; }
            //�����������肵�A�F��ς���
            if (playerHand == pcHand) {
                //������
                playerR = 255; playerG = 255; playerB = 255;
                pcR = 255;     pcG = 255;     pcB = 255;
            }
            else if ((playerHand + 1) % 3 == pcHand) {
                //�v���C���[����
                playerR = 255; playerG = 200; playerB = 200;
                pcR = 255;     pcG = 255;     pcB = 255;
            }
            else {
                //�o�b����
                playerR = 255; playerG = 255;  playerB = 255;
                pcR = 255;     pcG = 200;     pcB = 200;
            }
        }
        //�`��
        clear(200);
        rectMode(CENTER);
        imageColor(playerR, playerG, playerB);
        image(playerImg, playerPx, playerPy);
        imageColor(pcR, pcG, pcB);
        image(pcImg, pcPx, pcPy);
    }
}

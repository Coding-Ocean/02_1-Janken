#if 0


#else

#include"libOne.h"
void gmain(){
    //�E�B���h�E�\��
    window(800, 450);
    //�摜�ǂݍ���
    int playerGuImg    = loadImage("assets\\playerGu.png");
    int playerChokiImg = loadImage("assets\\playerChoki.png");
    int playerPaImg    = loadImage("assets\\playerPa.png");
    int pcGuImg        = loadImage("assets\\pcGu.png");
    int pcChokiImg     = loadImage("assets\\pcChoki.png");
    int pcPaImg        = loadImage("assets\\pcPa.png");
    int heartImg       = loadImage("assets\\heart.png");
    //��̔ԍ��萔�����߂Ă���
    const int GU    = 0;
    const int CHOKI = 1;
    const int PA    = 2;
    //�v���C���[�f�[�^
    int playerHand;
    int playerImg;
    int playerLife;
    float playerPx;
    float playerPy;
    float playerR;
    float playerG;
    float playerB;
    float playerAngle;
    //�o�b�f�[�^
    int pcHand;
    int pcImg;
    int pcLife;
    float pcPx;
    float pcPy;
    float pcR;
    float pcG;
    float pcB;
    float pcAngle;
    //�������������p
    float resultPx;
    float resultPy;
    float resultSize;
    //��Ԑ؂�ւ�
    const int INIT   = 0;
    const int PLAY   = 1;
    const int RESULT = 2;
    int state = INIT;
    //���C�����[�v
    while (notQuit) {
        //�f�[�^�X�V-----------------------------------------------------------
        if (state == INIT) {
            //�������O�����l�ݒ�
            //�v���C���[�f�[�^
            playerHand = GU;
            playerImg = playerGuImg;
            playerPx = 250;
            playerPy = 225;
            playerR = 255;
            playerG = 255;
            playerB = 255;
            playerLife = 3;
            playerAngle = 0;
            //�o�b�f�[�^
            pcHand = GU;
            pcImg = pcGuImg;
            pcPx = 550;
            pcPy = 225;
            pcR = 255;
            pcG = 255;
            pcB = 255;
            pcLife = 3;
            pcAngle = 0;
            //������������
            resultPx = 225;
            resultPy = 320;
            resultSize = 0;
            //�Q�[���X�e�[�g�؂�ւ�
            state = PLAY;
        }
        else if( state == PLAY ){
            //������
            //A,S,D�����ꂩ�̃L�[�������ꂽ��
            if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
                //�v���C���[�̎�����߂�---------------------------------------
                if      (isTrigger(KEY_A)) { playerHand = GU; }
                else if (isTrigger(KEY_S)) { playerHand = CHOKI; }
                else if (isTrigger(KEY_D)) { playerHand = PA; }
                //�v���C���[�̉摜��؂�ւ���
                if      (playerHand == GU   ) { playerImg = playerGuImg; }
                else if (playerHand == CHOKI) { playerImg = playerChokiImg; }
                else if (playerHand == PA   ) { playerImg = playerPaImg; }
                //�o�b�̎�����߂�---------------------------------------------
                pcHand = random() % 3;
                //�o�b�̉摜��؂�ւ���
                if      (pcHand == GU   ) { pcImg = pcGuImg; }
                else if (pcHand == CHOKI) { pcImg = pcChokiImg; }
                else if (pcHand == PA   ) { pcImg = pcPaImg; }
                //�����������肵�A�F��ς���-----------------------------------
                if (playerHand == pcHand) {
                    //������
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255;     pcG = 255;     pcB = 255;
                }
                else if ((playerHand + 1) % 3 == pcHand) {
                    //�v���C���[����
                    playerR = 255; playerG = 200; playerB = 200;
                    pcR = 255;     pcG = 255;     pcB = 255;
                    pcLife--;
                }
                else {
                    //�o�b����
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255;     pcG = 200;     pcB = 200;
                    playerLife--;
                }
                //�Q�[���X�e�[�g�؂�ւ�---------------------------------------
                if (playerLife == 0 || pcLife == 0) {
                    state = RESULT;
                }
            }
        }
        else if(state == RESULT){
            //�����I��---------------------------------------------------------
            if (pcLife == 0) {
                //�o�b����
                pcPy += 1.0f;
                pcAngle += -0.005f;
            }
            else {
                //�v���C���[����
                playerPy += 1.0f;
                playerAngle += 0.005f;
            }
            //��������������傫�����Ă���
            if (resultSize < 180) {
                resultSize += 10.0f;
            }
            //�Q�[���X�e�[�g�؂�ւ�-------------------------------------------
            if (isTrigger(KEY_SPACE)) {
                state = INIT;
            }
        }
        //�`��-----------------------------------------------------------------
        clear(200);
        //�v���C���[�̎�
        rectMode(CENTER);
        imageColor(playerR, playerG, playerB);
        image(playerImg, playerPx, playerPy,playerAngle);
        //�o�b�̎�
        imageColor(pcR, pcG, pcB);
        image(pcImg, pcPx, pcPy,pcAngle);
        //�v���C���[�n�[�g
        imageColor(255, 0, 0);
        for (int i = 0; i < playerLife; i++) {
            image(heartImg, playerPx - 50 + i * 50, playerPy - 110);
        }
        //�o�b�n�[�g
        for (int i = 0; i < pcLife; i++) {
            image(heartImg, pcPx - 50 + i * 50, pcPy - 110);
        }
        //���������e�L�X�g
        if (state == RESULT) {
            textSize(resultSize);
            if (playerLife > 0) {
                fill(255, 0, 0);
                text("����", resultPx, resultPy);
            }
            else {
                fill(0, 0, 200);
                text("����", resultPx, resultPy);
            }
        }
    }
}

#endif
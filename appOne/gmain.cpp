#if 1

#include"libOne.h"
struct DATA {
    int playerGuImg;   
    int playerChokiImg;
    int playerPaImg;   
    int pcGuImg;       
    int pcChokiImg;    
    int pcPaImg;
    int heartImg;

    const int GU = 0;
    const int CHOKI = 1;
    const int PA = 2;

    //�v���C���[�f�[�^�J�[�h
    int playerHand;
    int playerImg;
    int playerLife;
    float playerPx;
    float playerPy;
    float playerR;
    float playerG;
    float playerB;
    float playerAngle;
    //�o�b�f�[�^�J�[�h
    int pcHand;
    int pcImg;
    int pcLife;
    float pcPx;
    float pcPy;
    float pcR;
    float pcG;
    float pcB;
    float pcAngle;
    //�������������p�J�[�h
    float resultPx;
    float resultPy;
    float resultSize;
    //�V�[�P���X�J��
    const int INIT = 0;
    const int PLAY = 1;
    const int RESULT = 2;
    int state = INIT;
};
void draw(struct DATA* d);
void drawResult(struct DATA* d);
void loadImages(struct DATA* d) {
    d->playerGuImg = loadImage("assets\\playerGu.png");
    d->playerChokiImg = loadImage("assets\\playerChoki.png");
    d->playerPaImg = loadImage("assets\\playerPa.png");
    d->pcGuImg = loadImage("assets\\pcGu.png");
    d->pcChokiImg = loadImage("assets\\pcChoki.png");
    d->pcPaImg = loadImage("assets\\pcPa.png");
    d->heartImg = loadImage("assets\\heart.png");
}
void init(struct DATA* d) {
    //�v���C���[�f�[�^
    d->playerHand = d->GU;
    d->playerImg = d->playerGuImg;
    d->playerPx = 250;
    d->playerPy = 225;
    d->playerR = 255;
    d->playerG = 255;
    d->playerB = 255;
    d->playerLife = 3;
    d->playerAngle = 0;
    //�o�b�f�[�^
    d->pcHand = d->GU;
    d->pcImg = d->pcGuImg;
    d->pcPx = 550;
    d->pcPy = 225;
    d->pcR = 255;
    d->pcG = 255;
    d->pcB = 255;
    d->pcLife = 3;
    d->pcAngle = 0;
    //������������
    d->resultPx = 225;
    d->resultPy = 320;
    d->resultSize = 0;
    //�Q�[���X�e�[�g�؂�ւ�
    d->state = d->PLAY;
}
void play(struct DATA* d) {
    if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {

        if (isTrigger(KEY_A)) { d->playerHand = d->GU; }
        else if (isTrigger(KEY_S)) { d->playerHand = d->CHOKI; }
        else if (isTrigger(KEY_D)) { d->playerHand = d->PA; }
        if (d->playerHand == d->GU) { d->playerImg = d->playerGuImg; }
        else if (d->playerHand == d->CHOKI) { d->playerImg = d->playerChokiImg; }
        else if (d->playerHand == d->PA) { d->playerImg = d->playerPaImg; }

        d->pcHand = random() % 3;
        if (d->pcHand == d->GU) { d->pcImg = d->pcGuImg; }
        else if (d->pcHand == d->CHOKI) { d->pcImg = d->pcChokiImg; }
        else if (d->pcHand == d->PA) { d->pcImg = d->pcPaImg; }

        //�����������肵�A�F��ς���
        if (d->playerHand == d->pcHand) {
            //������
            d->playerR = 255; d->playerG = 255; d->playerB = 255;
            d->pcR = 255;     d->pcG = 255;     d->pcB = 255;
        }
        else if ((d->playerHand + 1) % 3 == d->pcHand) {
            //�v���C���[����
            d->playerR = 255; d->playerG = 200; d->playerB = 200;
            d->pcR = 255;     d->pcG = 255;     d->pcB = 255;
            d->pcLife--;
        }
        else {
            //�o�b����
            d->playerR = 255; d->playerG = 255; d->playerB = 255;
            d->pcR = 255;     d->pcG = 200;     d->pcB = 200;
            d->playerLife--;
        }
        //�Q�[���X�e�[�g�؂�ւ�
        if (d->playerLife == 0 || d->pcLife == 0) {
            d->state = d->RESULT;
        }
    }
    draw(d);
}
void result(struct DATA* d) {
    //�����I��
    if (d->pcLife == 0) {
        //�o�b����
        d->pcPy += 1.0f;
        d->pcAngle += -0.005f;
    }
    else {
        //�v���C���[����
        d->playerPy += 1.0f;
        d->playerAngle += 0.005f;
    }
    //�������������̑傫��
    if (d->resultSize < 180) {
        d->resultSize += 10.0f;
    }
    //�Q�[���X�e�[�g�؂�ւ�
    if (isTrigger(KEY_SPACE)) {
        d->state = d->INIT;
    }
    draw(d);
    drawResult(d);
}
void draw(struct DATA* d) {
    clear(200, 200, 200);
    //�v���C���[�̎�
    rectMode(CENTER);
    imageColor(d->playerR, d->playerG, d->playerB);
    image(d->playerImg, d->playerPx, d->playerPy, d->playerAngle);
    //�o�b�̎�
    imageColor(d->pcR, d->pcG, d->pcB);
    image(d->pcImg, d->pcPx, d->pcPy, d->pcAngle);
    //�v���C���[�n�[�g
    imageColor(255, 0, 0);
    for (int i = 0; i < d->playerLife; i++) {
        image(d->heartImg, d->playerPx - 50 + i * 50, d->playerPy - 110);
    }
    //�o�b�n�[�g
    for (int i = 0; i < d->pcLife; i++) {
        image(d->heartImg, d->pcPx - 50 + i * 50, d->pcPy - 110);
    }
}
void drawResult(struct DATA* d) {
    //���������e�L�X�g
    textSize(d->resultSize);
    if (d->playerLife > 0) {
        fill(255, 0, 0);
        text("����", d->resultPx, d->resultPy);
    }
    else {
        fill(0, 0, 200);
        text("����", d->resultPx, d->resultPy);
    }
}
void gmain() {
    window(800, 450);
    struct DATA d;
    loadImages(&d);
    while (notQuit) {
        if      (d.state == d.INIT) { init(&d); }
        else if (d.state == d.PLAY) { play(&d); }
        else if (d.state == d.RESULT) { result(&d); }
    }
}

#else

#include"libOne.h"
void gmain(){
    //�E�B���h�E�\���i���̖��߂͉摜�ǂݍ��݂��O�ɏo���Ȃ���΂Ȃ�Ȃ��j
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
    //�v���C���[�f�[�^�J�[�h
    int playerHand;
    int playerImg;
    int playerLife;
    float playerPx;
    float playerPy;
    float playerR;
    float playerG;
    float playerB;
    float playerAngle;
    //�o�b�f�[�^�J�[�h
    int pcHand;
    int pcImg;
    int pcLife;
    float pcPx;
    float pcPy;
    float pcR;
    float pcG;
    float pcB;
    float pcAngle;
    //�������������p�J�[�h
    float resultPx;
    float resultPy;
    float resultSize;
    //��Ԑ؂�ւ��J�[�h
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
                //�v���C���[�̎�����߂�
                if      (isTrigger(KEY_A)) { playerHand = GU; }
                else if (isTrigger(KEY_S)) { playerHand = CHOKI; }
                else if (isTrigger(KEY_D)) { playerHand = PA; }
                //�v���C���[�̉摜��؂�ւ���
                if      (playerHand == GU   ) { playerImg = playerGuImg; }
                else if (playerHand == CHOKI) { playerImg = playerChokiImg; }
                else if (playerHand == PA   ) { playerImg = playerPaImg; }
                //�o�b�̎�����߂�
                pcHand = random() % 3;
                //�o�b�̉摜��؂�ւ���
                if      (pcHand == GU   ) { pcImg = pcGuImg; }
                else if (pcHand == CHOKI) { pcImg = pcChokiImg; }
                else if (pcHand == PA   ) { pcImg = pcPaImg; }
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
                    pcLife--;
                }
                else {
                    //�o�b����
                    playerR = 255; playerG = 255; playerB = 255;
                    pcR = 255;     pcG = 200;     pcB = 200;
                    playerLife--;
                }
                //�Q�[���X�e�[�g�؂�ւ�
                if (playerLife == 0 || pcLife == 0) {
                    state = RESULT;
                }
            }
        }
        else if(state == RESULT){
            //�����I��
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
            //�������������̑傫��
            if (resultSize < 180) {
                resultSize += 10.0f;
            }
            //�Q�[���X�e�[�g�؂�ւ�
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
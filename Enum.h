#pragma once


enum class eDir
{
    Idle, Up, Left, Down, Right
};

enum class eCharacter
{
    Mom, Doctor_O, Osub, Nurse, Master, SubMaster, Mart
};

enum class eTerrain
{   
    Open = 0,           // �������
    Grass = 1,          // ���ϸ� ����
    Close = 2,          // ��������
    Door = 3,           // �� 1��
    BottomBlock = 4,    // �Ʒ�����(����)
    RightBlock = 5,     // �����ʸ���(����)
    LeftBlock = 6,      // ���ʸ���(����)
    
    
};

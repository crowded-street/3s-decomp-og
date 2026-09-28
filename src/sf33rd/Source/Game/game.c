#include "sf33rd/Source/Game/game.h"
#include "sf33rd/Source/Game/demo/demo00.h"
#include "sf33rd/Source/Game/demo/demo01.h"
#include "sf33rd/Source/Game/demo/demo02.h"
#include "sf33rd/Source/Game/effect/eff35.h"
#include "sf33rd/Source/Game/effect/eff58.h"
#include "sf33rd/Source/Game/effect/effect.h"
#include "sf33rd/Source/Game/effect/effj2.h"
#include "sf33rd/Source/Game/ending/end_main.h"
#include "sf33rd/Source/Game/engine/bbbscom.h"
#include "sf33rd/Source/Game/engine/cmb_win.h"
#include "sf33rd/Source/Game/engine/grade.h"
#include "sf33rd/Source/Game/engine/hitcheck.h"
#include "sf33rd/Source/Game/engine/manage.h"
#include "sf33rd/Source/Game/engine/plcnt.h"
#include "sf33rd/Source/Game/engine/plcnt2.h"
#include "sf33rd/Source/Game/engine/plcnt3.h"
#include "sf33rd/Source/Game/engine/slowf.h"
#include "sf33rd/Source/Game/engine/spgauge.h"
#include "sf33rd/Source/Game/engine/stun.h"
#include "sf33rd/Source/Game/engine/vital.h"
#include "sf33rd/Source/Game/engine/workuser.h"
#include "sf33rd/Source/Game/opening/opening.h"
#include "sf33rd/Source/Game/rendering/cg.h"
#include "sf33rd/Source/Game/rendering/color3rd.h"
#include "sf33rd/Source/Game/rendering/mmtmcnt.h"
#include "sf33rd/Source/Game/rendering/mtrans.h"
#include "sf33rd/Source/Game/screen/continue.h"
#include "sf33rd/Source/Game/screen/entry.h"
#include "sf33rd/Source/Game/screen/gameover.h"
#include "sf33rd/Source/Game/screen/next_cpu.h"
#include "sf33rd/Source/Game/screen/ranking.h"
#include "sf33rd/Source/Game/screen/sel_pl.h"
#include "sf33rd/Source/Game/screen/win.h"
#include "sf33rd/Source/Game/sound/cps3sound.h"
#include "sf33rd/Source/Game/sound/se.h"
#include "sf33rd/Source/Game/sound/sound3rd.h"
#include "sf33rd/Source/Game/stage/bg_sub.h"
#include "sf33rd/Source/Game/stage/ta_sub.h"
#include "sf33rd/Source/Game/stage/tate00.h"
#include "sf33rd/Source/Game/system/reset.h"
#include "sf33rd/Source/Game/system/sys_sub.h"
#include "sf33rd/Source/Game/system/sys_sub2.h"
#include "sf33rd/Source/Game/system/task.h"
#include "sf33rd/Source/Game/ui/count.h"
#include "sf33rd/Source/Game/ui/flash_lp.h"
#include "sf33rd/Source/Game/ui/sc_sub.h"

void Game_Task() {
    void (*Main_Jmp_Tbl[3])() = { Loop_Demo, Game, FUN_06096ce4 };

    for (;;) {
        Main_Jmp_Tbl[(s16)G_No[0]]();
        FUN_060d4f90();
        FUN_06137214();
        task_yield(1);
    }
}

void FUN_06094dae() {
    void (*Main_Jmp_Tbl[3])() = { Loop_Demo, Game, FUN_06096ce4 };

    Main_Jmp_Tbl[(s16)G_No[0]]();
}

void Loop_Demo() {
    if (Ck_Coin()) {
        FUN_06138918(0, 0x20);
        FUN_0608f6e8(0, 7, 0);

        if (G_No[1] != 99) {
            FUN_0613a334();
        }

        SsBgmControl(0, 0);
        FUN_060d3946();
        DAT_0202805c = 0;

        if (Demo_Flag == 0) {
            SsRequest(0x73);
        }

        G_No[0] = 1;
        G_No[1] = 0;
        G_No[2] = 0;
        G_No[3] = 0;
        D_No[0] = 0;
        D_No[1] = 0;
        D_No[2] = 0;
        D_No[3] = 0;
        Demo_Flag = 1;
        BGM_Stop();
        Before_Select_Sub();

        if (DAT_0200000c != 0) {
            G_No[2] = 4;
            FUN_06001c38();
            return;
        }

        E_No[0] = 1;
        E_No[1] = 0;
        E_No[2] = 0;
        E_No[3] = 0;

        return;
    }

    switch (G_No[1]) {
    case 0:
        G_No[1] = 1;
        G_No[2] = 0;
        G_No[3] = 0;
        D_No[0] = 0;
        D_No[1] = 0;
        D_No[2] = 0;
        D_No[3] = 0;
        E_No[1] = 99;
        Demo_PL_Index = 0;
        Demo_Stage_Index = 0;
        Select_Demo_Index = 0;
        ss_base_y = 0;
        Insert_Y = 0x17;
        Demo_Flag = 0;
        FUN_0608f6e8(0, 7, 0);
        ss_fill_a(0, 0x20);
        break;

    case 1:
        draw_system_info(ss_base_y);
        Basic_Sub();

        if (CAPCOM_Logo()) {
            Loop_Demo_Sub();
            clear_insert_y_message();
            Insert_Y = 0x17;
            E_No[1] = 2;
            DAT_0202805c = 0;
        }

        break;

    case 2:
        draw_system_info(ss_base_y);
        Basic_Sub();
        hit_check_main_process();

        if (Title()) {
            Loop_Demo_Sub();
            clear_insert_y_message();
            D_No[0] = 1;
            replay_flag = 0;
            Insert_Y = 0x11;
        }

        break;

    case 3:
        draw_system_info(ss_base_y);

        if (Play_Demo()) {
            Loop_Demo_Sub();
            Rank_Type = 0;
            Demo_Type = 0;
            ss_base_y = 0x20;
            FUN_0612e51c(4, 0, 0x100);
            FUN_0613a334();

            if (DAT_020156b2 == 3) {
                G_No[1] = 1;
                E_No[1] = 99;
                Select_Demo_Index += 1;

                if (3 < Select_Demo_Index) {
                    Select_Demo_Index = 0;
                }
            }
        }

        break;

    case 4:
        draw_system_info(ss_base_y);
        Basic_Sub();

        if (Ranking()) {
            Loop_Demo_Sub();
        }

        break;

    case 5:
        draw_system_info(ss_base_y);

        if (Play_Demo()) {
            Loop_Demo_Sub();
            Rank_Type = 5;
            Demo_Type = 1;
            ss_base_y = 0x20;
            FUN_0612e51c(4, 0, 0x100);
            FUN_0613a334();

            if (DAT_020156b2 == 3) {
                G_No[1] = 1;
                E_No[1] = 99;
            }
        }

        break;

    case 6:
        draw_system_info(ss_base_y);
        Basic_Sub();

        if (Ranking()) {
            Loop_Demo_Sub();
            G_No[1] = 1;
            E_No[1] = 99;
        }

        break;

    default:
        if (G_No[2] == 0) {
            Cover_Timer -= 1;

            if (Cover_Timer == 0) {
                G_No[2] = 1;
                FUN_060911e4(0, 0);
            }
        } else {
            G_No[1] = 1;
            G_No[2] = 0;
            E_No[3] = 0;
            E_No[1] = 99;
            Demo_PL_Index = 0;
            Demo_Stage_Index = 0;
            Select_Demo_Index = 0;
            ss_base_y = 0;
            Demo_Flag = 0;
        }

        break;
    }
}

void Loop_Demo_Sub() {
    G_No[1] += 1;
    G_No[2] = 0;
    D_No[0] = 0;
    D_No[1] = 0;
    D_No[2] = 0;
    D_No[3] = 0;
    E_No[1] = 1;
    FUN_0612e51c(4, 0, 0);
}

void clear_insert_y_message() {
    ss_put_string(DAT_020113e0 + 0xE, (int)Insert_Y, 0x12, "              ");
    ss_put_string(DAT_020113e0 + 0xE, Insert_Y + 0x20, 0x12, "              ");
}

void Before_Select_Sub() {
    Request_G_No = 0;
    Request_E_No = 0;
    Allow_a_battle_f = 0;
    Bonus_Type = 0;

    if (Demo_Flag == 0) {
        Control_Time = 0x800;
        Round_Level = 7;
    } else {
        Control_Time = 0x1E1;
    }

    Super_Arts[0] = 0;
    Super_Arts[1] = 0;
    Exec_Wipe = 0;
    Fade_Flag = 0;
    Stock_Com_Color[0] = -1;
    Stock_Com_Arts[0] = -1;
    Stock_Com_Color[1] = -1;
    Stock_Com_Arts[1] = -1;
    Bonus_Game_Flag = 0;
    Combo_Demo_Flag = 0;
    paring_counter[0] = 0;
    paring_bonus_r[0] = 0;
    paring_counter[1] = 0;
    paring_bonus_r[1] = 0;
    s16_02016b52 = 0x200;
    Clear_Disp_Ranking(0);
    Clear_Disp_Ranking(1);
    Clear_Personal_Data(0);
    grade_check_work_1st_init(0, 0);
    grade_check_work_1st_init(0, 1);
    Clear_Personal_Data(1);
    grade_check_work_1st_init(1, 0);
    grade_check_work_1st_init(1, 1);
    Player_Number = -1;
    Last_Player_id = -1;
    Round_Level = 3;
    Time_in_Time = 0x3C;
    Random_ix16 = (u16)system_timer & 0x3F;
    Random_ix32 = (u16)system_timer & 0x7F;
}

void Game() {
    void (*Game_Jmp_Tbl[12])() = { Game00, Game01, Game02, Game03, Game04, Game05,
                                   Game06, Game07, Game08, Game09, Game10, Game11 };

    Game_Jmp_Tbl[(s16)G_No[1]]();
}

void Game00() {
    void (*Game00_Jmp_Tbl[6])() = { Game0_0, Game0_1, Game0_2, Game0_3, Game0_2, Game0_3 };

    Game00_Jmp_Tbl[(s16)G_No[2]]();
    Basic_Sub();
}

void Game0_0() {
    if (FUN_060974ee()) {
        G_No[2] += 1;
    }
}

void Game0_1() {
    if (Request_G_No) {
        G_No[2] += 1;
    }
}

void Game0_2() {
    G_No[2] += 1;
    FUN_060d7396();
    FUN_060911e4(0, 1);
}

void Game0_3() {
    if (FUN_06091214()) {
        G_No[1] += 1;
        G_No[2] = 0;
        G_No[3] = 0;
        Cover_Timer = 23;
    }
}

void Game01() {
    Basic_Sub();
    Setup_Play_Type();

    switch (G_No[2]) {
    case 0:
        G_No[2] = 1;
        S_No[0] = 0;
        S_No[1] = 0;
        S_No[2] = 0;
        S_No[3] = 0;
        Break_Into = 0;
        Stop_Combo = 0;
        FUN_060d4df2(5);
        init_slow_flag();
        break;

    case 1:
        if (Select_Player()) {
            G_No[2] += 1;
            Bonus_Game_Flag = 0;
            FUN_060d4df2(2);
            Game01_Sub();
            FUN_060d7396();
            FUN_060911e4(3, 3);
        }

        break;

    default:
        Select_Player();

        if (FUN_06091214()) {
            Cover_Timer = 24;
            appear_type = 1;

            if (Demo_Flag == 0) {
                Demo_Time_Stop = 1;
                plw[0].wu.operator = 0;
                Operator_Status[0] = 0;
                plw[1].wu.operator = 0;
                Operator_Status[1] = 0;
            } else {
                G_No[1] = 2;
                G_No[2] = 0;
                E_No[0] = 4;
                E_No[1] = 0;
                E_No[2] = 0;
                E_No[3] = 0;
                replay_flag = 0;
            }

            cg_release_resident_resource(0x9060);

            if (plw[0].wu.operator != 0) {
                Sel_Arts_Complete[0] = -1;
            }

            if (plw[1].wu.operator != 0) {
                Sel_Arts_Complete[1] = -1;
            }

            if ((plw[0].wu.operator == 0) || (plw[1].wu.operator == 0)) {
                Play_Type = 0;
            } else {
                Play_Type = 1;
            }

            BGM_Stop();
        }

        break;
    }
}

void Game01_Sub() {
    ss_put_string(DAT_06194664[DAT_0206ac62], 0, 0x12, "                   ");
    ss_put_string(DAT_06194668[DAT_0206ac62], 0, 0x12, "                   ");
    vital_cont_init();
    combo_cont_init();
    count_cont_init(0);
    FUN_060d6124();
    FUN_060d6cc2();
    PL_Wins[0] = 0;
    PL_Wins[1] = 0;
    Score[0][1] = 0;
    Score[0][2] = 0;
    Score[1][1] = 0;
    Score[1][2] = 0;
    FUN_0609e73a();
    FUN_0609bfcc();
    Clear_Win_Type();
    FUN_06092026();
    Win_Mark_State[0] = 0;
    FUN_060d96b4(0);
    Win_Mark_State[1] = 0;
    FUN_060d96b4(1);
    set_kizetsu_status(0);
    set_kizetsu_status(1);
    set_super_arts_status(0);
    set_super_arts_status(1);

    if (Demo_Flag == 0) {
        spgauge_cont_demo_init();
    } else {
        spgauge_cont_init();
    }

    FUN_060d8456();
    stngauge_cont_init();
}

void Game05() {
    Basic_Sub();
    Setup_Play_Type();

    switch (G_No[2]) {
    case 0:
        G_No[2] = 1;
        SC_No[0] = 0;
        SC_No[1] = 0;
        SC_No[2] = 0;
        SC_No[3] = 0;

        if (Check_Bonus_Stage()) {
            SC_No[0] = 6;
        }

        Stop_Combo = 0;
        init_slow_flag();
        break;

    case 1:
        if (Next_CPU()) {
            G_No[2] += 1;

            if (Bonus_Type == 0) {
                Game01_Sub();
            }

            FUN_060d7396();
            FUN_060911e4(3, 3);
        }

        break;

    default:
        Next_CPU();

        if (FUN_06091214()) {
            Cover_Timer = 24;
            BGM_Stop();

            if (Bonus_Type == 0) {
                G_No[1] = 2;
                G_No[2] = 0;
                E_No[0] = 4;
                E_No[1] = 0;
                E_No[2] = 0;
                E_No[3] = 0;
                Bonus_Game_Flag = 0;
            } else {
                G_No[1] = 9;
                G_No[2] = 0;
                G_No[3] = 0;
                E_No[0] = 4;
                E_No[1] = 0;
                E_No[2] = 0;
                E_No[3] = 0;
            }
        }

        break;
    }
}

void Game11() {
    Basic_Sub();
    Setup_Play_Type();

    switch (G_No[2]) {
    case 0:
        G_No[2] += 1;
        SC_No[0] = 0;
        SC_No[1] = 0;
        SC_No[2] = 0;
        SC_No[3] = 0;
        Stop_Combo = 0;
        Bonus_Type = 0;
        init_slow_flag();
        break;

    case 1:
        if (Next_Q()) {
            G_No[2] += 1;
            Game01_Sub();
            FUN_060d7396();
            FUN_060911e4(3, 3);
        }

        break;

    case 2:
        Next_Q();

        if (FUN_06091214()) {
            Cover_Timer = 24;
            BGM_Stop();

            if (Bonus_Type == 0) {
                G_No[1] = 2;
                Bonus_Game_Flag = 0;
            } else {
                G_No[1] = 9;
                G_No[3] = 0;
            }

            G_No[2] = 0;
            E_No[0] = 4;
            E_No[1] = 0;
            E_No[2] = 0;
            E_No[3] = 0;
        }

        break;

    case 3:
        G_No[2] += 1;
        SC_No[0] = 0;
        SC_No[1] = 0;
        SC_No[2] = 0;
        SC_No[3] = 0;
        Stop_Combo = 0;
        Bonus_Type = 0;
        init_slow_flag();
        FUN_060d7396();
        FUN_060911e4(3, 3);
        break;

    case 4:
        if (FUN_06091214()) {
            G_No[2] = 1;
            Cover_Timer = 24;
        }

        break;
    }
}

void Game02() {
    void (*Game02_Jmp_Tbl[6])() = { Game2_0, Game2_1, Game2_2, Game2_3, Game2_4, Game2_5 };

    Scene_Cut = Cut_Cut_Cut();
    Game02_Jmp_Tbl[(s16)G_No[2]]();
}

void Game2_0() {
    FUN_06090f7e();
    _DAT_02011370 = 0xF;
    Game_timer = 0;
    Game_pause = 0;
    Demo_Time_Stop = 0;
    C_No[0] = 0;
    C_No[1] = 0;
    C_No[2] = 0;
    C_No[3] = 0;
    G_No[2] = 3;
    G_Timer = 10;
    DAT_02016d88 = 0x80;
    Round_num = 0;
    Allow_a_battle_f = 0;
    Time_in_Time = 0x3C;
    init_slow_flag();
    effect_work_quick_init();
    clear_hit_queue();
    pcon_rno[3] = 0;
    pcon_rno[2] = 0;
    pcon_rno[1] = 0;
    pcon_rno[0] = 0;
    ca_check_flag = 1;
    bg_work_clear();
    win_lose_work_clear();
    TATE00();
}

void Game2_1() {
    Game_timer += 1;
    set_EXE_flag();
    Time_Control();
    Player_control();
    vital_cont_main();
    combo_cont_main();
    TATE00();
    Game_Management();
    FUN_060d96b4(0);
    FUN_060d96b4(1);
    move_effect_work(0);
    move_effect_work(1);
    move_effect_work(2);
    move_effect_work(3);
    move_effect_work(4);
    move_effect_work(5);
    move_effect_work(6);
    hit_check_main_process();
}

void Game2_2() {}

void Game2_3() {
    Game2_1();
    G_Timer -= 1;

    if (G_Timer == 0) {
        G_No[2] = 1;
        Clear_Flash_No();
    }
}

void Game2_4() {
    if (G_No[3] == 0) {
        G_No[3] = 1;
        FUN_06090f7e();
        vital_cont_init();
        stngauge_work_clear();
        combo_cont_init();
        count_cont_init(1);
        Score[0][2] = 0;
        Score[1][2] = 0;
        FUN_0609e73a();
        Win_Mark_State[0] = 0;
        FUN_060d96b4(0);
        Win_Mark_State[1] = 0;
        FUN_060d96b4(1);
        Game_pause = 0;
        pcon_rno[0] = 0;
        pcon_rno[1] = 0;
        pcon_rno[2] = 0;
        pcon_rno[3] = 0;
        appear_type = 2;
        erase_extra_plef_work();
        bg_work_clear();
        win_lose_work_clear();

        if (bg_w.area < 2) {
            bg_w.area += 1;
        }

        TATE00();
        return;
    }

    Game2_1();
    G_Timer -= 1;

    if (G_Timer == 0) {
        G_No[2] = 1;
        Clear_Flash_No();
    }
}

void Game2_5() {
    if (G_No[3] == 0) {
        G_No[3] = 1;
        vital_cont_init();
        stngauge_work_clear();
        combo_cont_init();
        count_cont_init(1);
        Score[0][2] = 0;
        Score[1][2] = 0;
        FUN_0609e73a();
        Win_Mark_State[0] = 0;
        FUN_060d96b4(0);
        Win_Mark_State[1] = 0;
        FUN_060d96b4(1);
        Suicide[0] = 1;
        Game_pause = 0;
        pcon_rno[0] = 0;
        pcon_rno[1] = 0;
        pcon_rno[2] = 0;
        pcon_rno[3] = 0;
        appear_type = 0;
        erase_extra_plef_work();
        compel_bg_init_position();
        win_lose_work_clear();

        if (bg_w.area < 2) {
            bg_w.area += 1;
        }

        TATE00();

        if (DAT_020113c2 != 0) {
            FUN_060d4e56(DAT_0619de02[bg_w.unk_4a], 0x1F, 0x1F, 0x1F);
            FUN_060d4e56(DAT_0619ddd4[bg_w.unk_4a], 0x1F, 0x1F, 0x1F);
        }
    } else {
        Game2_1();
        G_Timer -= 1;

        if (G_Timer == 0) {
            G_No[2] = 1;
            Clear_Flash_No();
        }
    }
}

void Game03() {
    move_effect_work(4);
    move_effect_work(5);

    if (G_No[2] != 0 || !Winner_Scene()) {
        return;
    }

    if (FUN_0609cd00()) {
        Forbid_Break = 1;
        return;
    }

    if (DAT_0206ac67) {
        G_No[1] = 6;
        G_No[2] = 0;
        G_No[3] = 0;
        E_No[0] = 8;
        E_No[1] = 0;
        E_No[2] = 0;
        E_No[3] = 0;
        return;
    }

    G_No[1] = 5;
    G_No[2] = 0;
    E_No[0] = 9;
    E_No[1] = 0;
    E_No[2] = 0;
    E_No[3] = 0;

    if (Battle_Q[WINNER]) {
        G_No[1] = 11;
        G_No[2] = 3;
    }

    G_No[3] = 0;
    Cover_Timer = 24;

    if (DAT_02000006 && Round_Operator[LOSER]) {
        E_Number[LOSER][0] = 1;
        E_Number[LOSER][1] = 0;
        E_Number[LOSER][2] = 0;
        E_Number[LOSER][3] = 0;
    }
}

void Game04() {
    move_effect_work(4);
    move_effect_work(5);

    if (G_No[2] != 0 || !Loser_Scene()) {
        return;
    }

    if (DAT_02000006 == 0) {
        G_No[1] = 6;
        G_No[2] = 0;
        G_No[3] = 0;
        E_No[0] = 8;
        E_No[1] = 0;
        E_No[2] = 0;
        E_No[3] = 0;
        return;
    }

    G_No[1] = 7;
    G_No[2] = 0;
    G_No[3] = 0;
    E_No[0] = 7;
    E_No[1] = 0;
    E_No[2] = 0;
    E_No[3] = 0;
    Cont_No[0] = 0;
    Cont_No[1] = 0;
    Cont_No[2] = 0;
    Cont_No[3] = 0;
    E_Number[LOSER][0] = 1;
    E_Number[LOSER][1] = 0;
    E_Number[LOSER][2] = 0;
    E_Number[LOSER][3] = 0;
}

void Game09() {
    switch (G_No[2]) {
    case 0:
        FUN_06090f7e();
        Bonus_Game_Flag = (s16)Bonus_Type;
        _DAT_02011370 = 0xF;
        Game_timer = 0;
        Game_pause = 0;
        Demo_Time_Stop = 0;
        C_No[0] = 0;
        C_No[1] = 0;
        C_No[2] = 0;
        C_No[3] = 0;
        G_No[2] += 1;
        Round_num = 0;
        Allow_a_battle_f = 0;
        Time_in_Time = 0x3C;
        init_slow_flag();
        effect_work_quick_init();
        clear_hit_queue();
        pcon_rno[3] = 0;
        pcon_rno[2] = 0;
        pcon_rno[1] = 0;
        pcon_rno[0] = 0;
        FUN_0612cfde();
        ca_check_flag = 1;
        _DAT_02016b3c = 0x14;
        DAT_02016b3e = 0;
        _DAT_02016b40 = 0;
        bg_work_clear();
        win_lose_work_clear();
        bg_w.stage = Bonus_Type;
        bg_w.area = 0;

        if (Bonus_Game_Flag == 0x16) {
            My_char[COM_id] = 12;
        } else {
            My_char[COM_id] = My_char[Player_id];
        }

        FUN_060a28c4();
        Setup_PL_Color((s16)COM_id, _DAT_0201575a);
        TATE00();
        break;

    case 1:
        G_No[2] += 1;
        G_Timer = 0x13;

        if (Bonus_Type == 22) {
            FUN_0612cfec((int)COM_id);
            effect_35_init(0x3C, 5);
            FUN_0610cb1c(0x78);
            effect_35_init(0xB4, 7);
            effect_58_init(6, 0xB4, 0xA1);
        } else {
            effect_35_init(0x3C, 6);
            effect_35_init(0x78, 7);
            effect_58_init(6, 0x78, 0xA1);
        }

        break;

    case 2:
        Bonus_Sub();
        G_Timer -= 1;

        if (G_Timer == 0) {
            G_No[2] += 1;
            Clear_Flash_No();
            ss_base_y = 0;
            FUN_0612e51c(4, 0, 0);
            FUN_060911e4(0, 1);
        }

        break;

    case 3:
        Bonus_Sub();

        if (unk_wipe()) {
            G_No[2] += 1;
            Forbid_Break = 0;
        }

        break;

    case 4:
        if (Bonus_Sub() != 0) {
            G_No[2] += 1;
            Cover_Timer = 24;
            FUN_060d7396();
            Stop_Combo = 1;
            FUN_060911e4(3, 3);
        }

        break;

    case 5:
        Bonus_Sub();

        if (FUN_06091214()) {
            effect_work_quick_init();
            FUN_0608fba8();
            Clear_Flash_No();
            Cover_Timer = 24;
            Suicide[0] = 1;
            FUN_06090f7e();
            FUN_06138918(0, 0x20);
            G_No[1] = 10;
            G_No[2] = 0;
            G_No[3] = 0;
            E_No[0] = 9;
            E_No[1] = 0;
            E_No[2] = 0;
            E_No[3] = 0;
            FUN_060d4df2(2);
        }

        break;
    }
}

s16 Bonus_Sub() {
    s16 status;

    Scene_Cut = Cut_Cut_Cut();
    Bonus_Game_Complete = 0;
    Game_timer += 1;
    set_EXE_flag();
    Time_Control();

    if (Bonus_Type == 22) {
        Bonus_Game_Complete = Player_control_bonus();
    } else {
        Bonus_Game_Complete = Player_control_bonus2();
    }

    TATE00();
    status = Game_Management();
    move_effect_work(0);
    move_effect_work(1);
    move_effect_work(2);
    move_effect_work(3);
    move_effect_work(4);
    move_effect_work(5);
    move_effect_work(6);
    hit_check_main_process();
    return status;
}

void Game10() {
    Basic_Sub();
    Setup_Play_Type();

    switch (G_No[2]) {
    case 0:
        G_No[2] = 1;
        SC_No[0] = 0;
        SC_No[1] = 0;
        SC_No[2] = 0;
        SC_No[3] = 0;
        Stop_Combo = 0;
        init_slow_flag();
        break;

    case 1:
        if (After_Bonus()) {
            G_No[2] += 1;
            FUN_060d4df2(2);
            Game01_Sub();
            FUN_060d7396();
            FUN_060911e4(3, 3);
        }

        break;

    default:
        if (After_Bonus() && FUN_06091214()) {
            Cover_Timer = 24;
            BGM_Stop();
            G_No[1] = 2;
            G_No[2] = 0;
            E_No[0] = 4;
            E_No[1] = 0;
            E_No[2] = 0;
            E_No[3] = 0;
            Bonus_Game_Flag = 0;
        }

        break;
    }
}

void Game08() {
    switch (G_No[2]) {
    case 0:
        G_No[2] = 1;
        Final_Result_id = WINNER;
        WGJ_Target = WINNER;
        WGJ_Win = Win_Record[WINNER];
        grade_final_grade_bonus();
        WGJ_Score = Score[WINNER][0] + (u32)Continue_Coin[WINNER];
        break;

    case 1:
        if (Ending_main(End_PL) && FUN_060910e0(0x6B, 0)) {
            G_No[2] += 1;
        }

        break;

    case 2:
        if (FUN_06091044()) {
            G_No[2] += 1;
            G_Timer = 10;
            Suicide[4] = 1;
        }

        break;

    case 3:
        G_Timer -= 1;

        if (G_Timer == 0) {
            G_No[1] = 6;
            G_No[2] = 0;
            E_No[0] = 8;
            E_No[1] = 0;
            E_No[2] = 0;
            E_No[3] = 0;
            Clear_Personal_Data(0);
            Clear_Personal_Data(1);
            plw[0].wu.operator = 0;
            plw[1].wu.operator = 0;
            Operator_Status[0] = 0;
            Operator_Status[1] = 0;
            Player_Number = -1;
            Last_Player_id = -1;
            FUN_060d4df2(2);
            FUN_060d4df2(5);
        }

        break;

    case 4:
        if (FUN_0609dc20()) {
            G_No[1] = 6;
            G_No[2] = 0;
            E_No[0] = 8;
            E_No[1] = 0;
            E_No[2] = 0;
            E_No[3] = 0;
            Clear_Personal_Data((s16)WINNER);
            plw[WINNER].wu.operator = 0;
            Operator_Status[WINNER] = 0;
            Player_Number = -1;
            Last_Player_id = -1;
        }

        break;
    }

    move_effect_work(4);
}

void Game06() {
    Basic_Sub_Ex();

    if (Break_Into) {
        return;
    }

    switch (G_No[2]) {
    case 0:
        G_No[2] += 1;
        Stock_Com_Color[Player_id] = -1;
        Stock_Com_Arts[Player_id] = -1;
        Last_Player_id = -1;
        Control_Time = 481;
        E_No[0] = 8;
        E_No[1] = 0;
        E_No[2] = 0;
        E_No[3] = 0;
        DAT_02016d31 = 0;
        DAT_02016d32 = 0;
        DAT_02016d33 = 0;
        DAT_02016d34 = 0;
        break;

    case 1:
        if (Game_Over()) {
            G_Timer = 60;

            if (Check_Disp_Ranking()) {
                G_No[2] += 1;
            } else {
                G_No[2] = 3;
            }
        }

        break;

    case 2:
        if (Disp_Ranking()) {
            G_No[2] += 1;
            G_Timer = 1;
        }

        break;

    case 3:
        if (--G_Timer == 0) {
            G_No[2] += 1;
            Clear_Disp_Ranking(0);
            Clear_Disp_Ranking(1);
            FUN_060d7396();
            FUN_060911e4(0, 1);
        }

        break;

    case 4:
        if (!FUN_06091214()) {
            break;
        }

        Cover_Timer = 24;
        Forbid_Break = 0;
        Clear_Flash_No();
        Clear_Personal_Data(LOSER);
        grade_check_work_1st_init(LOSER, 0);
        grade_check_work_1st_init(LOSER, 1);
        ss_fill_a(0, 0x20);

        if (Request_Break[0] == 0 && Request_Break[1] == 0) {
            G_No[0] = 0;
            G_No[1] = 99;
            G_No[2] = 0;
            G_No[3] = 0;
            E_No[0] = 0;
            E_No[1] = 99;
            E_No[2] = 0;
            E_No[3] = 0;
            D_No[0] = 0;
            D_No[1] = 0;
            D_No[2] = 0;
            D_No[3] = 0;
            DAT_02016b72 = 0;
            Combo_Demo_Flag = 0;
            FUN_06090f7e();
            return;
        }

        Request_Break_Sub(0);
        Request_Break_Sub(1);
        G_No[1] = 1;
        G_No[2] = 0;
        G_No[3] = 0;
        E_No[0] = 2;
        E_No[1] = 0;
        E_No[2] = 0;
        E_No[3] = 0;
        break;

    case 5:
        G_No[2] += 1;
        Stock_Com_Color[Player_id] = -1;
        Stock_Com_Arts[Player_id] = -1;
        Last_Player_id = -1;
        Clear_Personal_Data(Player_id);
        plw[Player_id].wu.operator = 0;
        Operator_Status[Player_id] = 0;
        grade_check_work_1st_init(Player_id, 0);
        grade_check_work_1st_init(Player_id, 1);
        Control_Time = 481;
        E_No[0] = 8;
        E_No[1] = 0;
        E_No[2] = 0;
        E_No[3] = 0;
        DAT_02016d31 = 2;
        DAT_02016d32 = 1;
        break;

    case 6:
        if (Game_Over()) {
            G_No[2] = 2;
            G_Timer = 60;
        }

        break;
    }
}

s32 Check_Disp_Ranking() {
    s16 rank_type;

    if (DAT_020156b2 == 3) {
        return 0;
    }

    rank_type = Disp_Rank_Sub(0);

    if (rank_type != -1) {
        Rank_Type = (s8)rank_type;
        Present_Rank[0] = Rank_In[0][rank_type];
        Present_Rank[1] = Rank_In[1][rank_type];
        return 1;
    }

    rank_type = Disp_Rank_Sub(1);

    if (rank_type != -1) {
        Rank_Type = (s8)rank_type;
        Present_Rank[1] = Rank_In[1][rank_type];
        return 1;
    }

    return 0;
}

s16 Disp_Rank_Sub(s16 PL_id) {
    if (-1 < Request_Disp_Rank[PL_id][3]) {
        return 0xF;
    }

    if (-1 < Request_Disp_Rank[PL_id][2]) {
        return 10;
    }

    if (-1 < Request_Disp_Rank[PL_id][1]) {
        return 5;
    }

    if (-1 < Request_Disp_Rank[PL_id][0]) {
        return 0;
    }

    return -1;
}

u32 FUN_06096b2c() {
    if ((-1 < Request_Disp_Rank[0][0]) || (-1 < Request_Disp_Rank[0][1])) {
        return 1;
    }

    if ((Request_Disp_Rank[1][0] < 0) && (Request_Disp_Rank[1][1] < 0)) {
        return 0;
    }

    return 1;
}

void Request_Break_Sub(s16 PL_id) {
    if (Request_Break[PL_id] && FUN_060044ac(0, 0, PL_id)) {
        plw[PL_id].wu.operator = 1;
        Operator_Status[PL_id] = 1;
    }
}

s32 Disp_Ranking() {
    switch (G_No[3]) {
    case 0:
        G_No[3] = 1;
        FUN_060d7396();
        FUN_060911e4(0, 0);
        break;

    case 1:
        if (FUN_06091214()) {
            Cover_Timer = 24;
            G_No[3] += 1;
            D_No[0] = 1;
            D_No[1] = 0;
            D_No[2] = 0;
            D_No[3] = 0;
            Clear_Personal_Data(0);
            grade_check_work_1st_init(0, 0);
            grade_check_work_1st_init(0, 1);
            Clear_Personal_Data(1);
            grade_check_work_1st_init(1, 0);
            grade_check_work_1st_init(1, 1);
        }

        break;

    case 2:
        Ranking();
        Cover_Timer -= 1;

        if (Cover_Timer == 0) {
            G_No[3] += 1;
            FUN_060911e4(0, 0);
        }

        break;

    case 3:
        Ranking();

        if (unk_wipe()) {
            G_No[3] += 1;
            Forbid_Break = 0;
            FUN_0608fb6a(7);
        }

        break;

    default:
        if (Ranking()) {
            BGM_Stop();
            return 1;
        }

        break;
    }

    return 0;
}

void Game07() {
    Basic_Sub();

    if (G_No[2] == 0 && Continue_Scene()) {
        G_No[1] = 6;
        G_No[2] = 0;
    }
}

void FUN_06096ce4() {}

void Time_Control() {
    if (!Allow_a_battle_f || Demo_Time_Stop || Bonus_Game_Flag) {
        return;
    }

    counter_control();

    if (Control_Time >= Limit_Time) {
        Control_Time = Limit_Time;
    } else if (--Time_in_Time == 0) {
        Time_in_Time = 60;
        Control_Time += 1;
    }
}

s16 Ck_Coin() {
    s16 PL_id = -1;

    if (DAT_0200000c == 0) {
        if (DAT_0206aa72 == 0 && DAT_0206aa7a == 0) {
            return (s8)(DAT_0206aa75 | DAT_0206aa6d | DAT_02007ce0 | DAT_02007ce1);
        }

        return 1;
    }

    if (~p1sw_1 & p1sw_0 & 0x1000) {
        PL_id = 0;
    } else if (~p2sw_1 & p2sw_0 & 0x1000) {
        PL_id = 1;
    }

    if (PL_id == -1) {
        return 0;
    }

    DAT_0202805c = 0;
    FUN_06133974();

    if (DAT_0206ac67 == 0) {
        plw[PL_id].wu.operator = 1;
        Operator_Status[PL_id] = 1;
        Champion = PL_id;
        plw[PL_id ^ 1].wu.operator = 0;
        Operator_Status[PL_id ^ 1] = 0;
    } else {
        plw[0].wu.operator = 1;
        plw[1].wu.operator = 1;
        Operator_Status[0] = 1;
        Operator_Status[1] = 1;
    }

    return 1;
}

void draw_system_info(s32 base_y) {
    if (Country != 6 && Country != 5) {
        return;
    }

    if (!(p1sw_0 & 0x10)) {
        ss_clear_rect(DAT_02011404 + 31, base_y + 20, DAT_02011404 + 49, base_y + 23);
        return;
    }

    ss_put_string(DAT_02011404 + 36, base_y + 20, 0x12, "GAME DATA");
    ss_put_string(DAT_02011404 + 31, base_y + 21, 0x12, "INCOME");
    ss_put_string(DAT_02011404 + 31, base_y + 22, 0x12, "SERVICE");
    ss_put_string(DAT_02011404 + 31, base_y + 23, 0x12, "CARD");
    FUN_06138d2c(DAT_02011404 + 41, (s16)(base_y + 21), 0x12, FUN_0612dab8(DAT_0206ab48), 6, 0);
    FUN_06138d2c(DAT_02011404 + 41, (s16)(base_y + 22), 0x12, FUN_0612dab8(DAT_0206ab4c), 6, 0);
    FUN_06138d2c(DAT_02011404 + 41, base_y + 23, 0x12, FUN_0612dab8(DAT_0206ab54), 6, 0);
}

/*
 * Standards.c
 *
 *  Created on: 15.02.2013
 *      Author: skuser
 *
 *  ChangeLog
 *    2019-09-22    Willok    Add Turn on the antenna load when simulation tags. It solves the problem of blind area in the short distance of reading head.
 *
 */

#include "Configuration.h"
#include "Settings.h"
#include <avr/pgmspace.h>
#include "Map.h"
#include "AntennaLevel.h"

/* Map IDs to text */
static const MapEntryType PROGMEM ConfigurationMap[] = {
    { .Id = CONFIG_NONE, 			.Text = "NONE" },
#ifdef CONFIG_MF_ULTRALIGHT_SUPPORT
    { .Id = CONFIG_MF_ULTRALIGHT, 	.Text = "MF_ULTRALIGHT" },
    { .Id = CONFIG_MF_ULTRALIGHT_EV1_80B,   .Text = "MF_ULTRALIGHT_EV1_80B" },
    { .Id = CONFIG_MF_ULTRALIGHT_EV1_164B,   .Text = "MF_ULTRALIGHT_EV1_164B" },
    {.Id = CONFIG_MF_ULTRALIGHT_C, .Text = "MF_ULTRALIGHT_C"},
#endif
#ifdef CONFIG_MF_CLASSIC_MINI_4B_SUPPORT
    { .Id = CONFIG_MF_CLASSIC_MINI_4B, 	.Text = "MF_CLASSIC_MINI_4B" },
#endif
#ifdef CONFIG_MF_CLASSIC_1K_SUPPORT
    { .Id = CONFIG_MF_CLASSIC_1K, 	.Text = "MF_CLASSIC_1K" },
#endif
#ifdef CONFIG_MF_CLASSIC_1K_7B_SUPPORT
    { .Id = CONFIG_MF_CLASSIC_1K_7B, 	.Text = "MF_CLASSIC_1K_7B" },
#endif
#ifdef CONFIG_MF_CLASSIC_4K_SUPPORT
    { .Id = CONFIG_MF_CLASSIC_4K, 	.Text = "MF_CLASSIC_4K" },
#endif
#ifdef CONFIG_MF_CLASSIC_4K_7B_SUPPORT
    { .Id = CONFIG_MF_CLASSIC_4K_7B, 	.Text = "MF_CLASSIC_4K_7B" },
#endif
#ifdef CONFIG_MF_DETECTION_SUPPORT
    { .Id = CONFIG_MF_DETECTION,   .Text = "MF_DETECTION_1K" },
#endif
#ifdef CONFIG_MF_DETECTION_4K_SUPPORT
    { .Id = CONFIG_MF_DETECTION_4K,    .Text = "MF_DETECTION_4K" },
#endif
#ifdef CONFIG_ISO14443A_SNIFF_SUPPORT
    { .Id = CONFIG_ISO14443A_SNIFF,	.Text = "ISO14443A_SNIFF" },
#endif
#ifdef CONFIG_ISO14443A_READER_SUPPORT
    { .Id = CONFIG_ISO14443A_READER,	.Text = "ISO14443A_READER" },
#endif
#ifdef CONFIG_NTAG215_SUPPORT
    { .Id = CONFIG_NTAG215,	.Text = "NTAG215" },
#endif
#ifdef CONFIG_VICINITY_SUPPORT
    { .Id = CONFIG_VICINITY,	.Text = "VICINITY" },
#endif
#ifdef CONFIG_ISO15693_SNIFF_SUPPORT
    { .Id = CONFIG_ISO15693_SNIFF,	.Text = "ISO15693_SNIFF" },
#endif
#ifdef CONFIG_SL2S2002_SUPPORT
    { .Id = CONFIG_SL2S2002,	.Text = "SL2S2002" },
#endif
#ifdef CONFIG_TITAGITSTANDARD_SUPPORT
    { .Id = CONFIG_TITAGITSTANDARD,	.Text = "TITAGITSTANDARD" },
#endif
#ifdef CONFIG_EM4233_SUPPORT
    { .Id = CONFIG_EM4233,	.Text = "EM4233" },
#endif
};

/* Include all Codecs and Applications */
#include "Codec/Codec.h"
#include "Application/Application.h"

static void CodecInitDummy(void) { }
static void CodecDeInitDummy(void) { }
static void CodecTaskDummy(void) { }
static void ApplicationInitDummy(void) {}
static void ApplicationResetDummy(void) {}
static void ApplicationTaskDummy(void) {}
static void ApplicationTickDummy(void) {}
static uint16_t ApplicationProcessDummy(uint8_t *ByteBuffer, uint16_t ByteCount) { return 0; }
static void ApplicationGetUidDummy(ConfigurationUidType Uid) { }
static void ApplicationSetUidDummy(ConfigurationUidType Uid) { }
static void ApplicationGetAtqaDummy(uint16_t * Atqa) { *Atqa = CONFIGURATION_DUMMY_ATQA; }
static void ApplicationSetAtqaDummy(uint16_t Atqa) { }
static void ApplicationGetSakDummy(uint8_t * Sak) { *Sak = CONFIGURATION_DUMMY_SAK; }
static void ApplicationSetSakDummy(uint8_t Sak) { }

static const PROGMEM ConfigurationType ConfigurationTable[] = {
    [CONFIG_NONE] = {
        .CodecInitFunc = CodecInitDummy,
        .CodecDeInitFunc = CodecDeInitDummy,
        .CodecTaskFunc = CodecTaskDummy,
        .ApplicationInitFunc = ApplicationInitDummy,
        .ApplicationResetFunc = ApplicationResetDummy,
        .ApplicationTaskFunc = ApplicationTaskDummy,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = ApplicationProcessDummy,
        .ApplicationGetUidFunc = ApplicationGetUidDummy,
        .ApplicationSetUidFunc = ApplicationSetUidDummy,
        .ApplicationGetSakFunc = ApplicationGetSakDummy,
        .ApplicationSetSakFunc = ApplicationSetSakDummy,
        .ApplicationGetAtqaFunc = ApplicationGetAtqaDummy,
        .ApplicationSetAtqaFunc = ApplicationSetAtqaDummy,
        .UidSize = 0,
        .MemorySize = 0,
        .ReadOnly = true,
        .TagFamily = TAG_FAMILY_NONE
    },
#ifdef CONFIG_MF_ULTRALIGHT_SUPPORT
    [CONFIG_MF_ULTRALIGHT] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareUltralightAppInit,
        .ApplicationResetFunc = MifareUltralightAppReset,
        .ApplicationTaskFunc = MifareUltralightAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareUltralightAppProcess,
        .ApplicationGetUidFunc = MifareUltralightGetUid,
        .ApplicationSetUidFunc = MifareUltralightSetUid,
        .ApplicationGetSakFunc = MifareUltralightGetSak,
        .ApplicationSetSakFunc = MifareUltralightSetSak,
        .ApplicationGetAtqaFunc = MifareUltralightGetAtqa,
        .ApplicationSetAtqaFunc = MifareUltralightSetAtqa,
        .UidSize = MIFARE_ULTRALIGHT_UID_SIZE,
        .MemorySize = MIFARE_ULTRALIGHT_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
    [CONFIG_MF_ULTRALIGHT_C] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareUltralightCAppInit,
        .ApplicationResetFunc = MifareUltralightCAppReset,
        .ApplicationTaskFunc = MifareUltralightAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareUltralightAppProcess,
        .ApplicationGetUidFunc = MifareUltralightGetUid,
        .ApplicationSetUidFunc = MifareUltralightSetUid,
        .ApplicationGetSakFunc = MifareUltralightGetSak,
        .ApplicationSetSakFunc = MifareUltralightSetSak,
        .ApplicationGetAtqaFunc = MifareUltralightGetAtqa,
        .ApplicationSetAtqaFunc = MifareUltralightSetAtqa,
        .UidSize = MIFARE_ULTRALIGHT_UID_SIZE,
        .MemorySize = MIFARE_ULTRALIGHTC_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
    [CONFIG_MF_ULTRALIGHT_EV1_80B] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareUltralightEV11AppInit,
        .ApplicationResetFunc = MifareUltralightAppReset,
        .ApplicationTaskFunc = MifareUltralightAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareUltralightAppProcess,
        .ApplicationGetUidFunc = MifareUltralightGetUid,
        .ApplicationSetUidFunc = MifareUltralightSetUid,
        .ApplicationGetSakFunc = MifareUltralightGetSak,
        .ApplicationSetSakFunc = MifareUltralightSetSak,
        .ApplicationGetAtqaFunc = MifareUltralightGetAtqa,
        .ApplicationSetAtqaFunc = MifareUltralightSetAtqa,
        .UidSize = MIFARE_ULTRALIGHT_UID_SIZE,
        .MemorySize = MIFARE_ULTRALIGHT_EV11_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
    [CONFIG_MF_ULTRALIGHT_EV1_164B] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareUltralightEV12AppInit,
        .ApplicationResetFunc = MifareUltralightAppReset,
        .ApplicationTaskFunc = MifareUltralightAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareUltralightAppProcess,
        .ApplicationGetUidFunc = MifareUltralightGetUid,
        .ApplicationSetUidFunc = MifareUltralightSetUid,
        .ApplicationGetSakFunc = MifareUltralightGetSak,
        .ApplicationSetSakFunc = MifareUltralightSetSak,
        .ApplicationGetAtqaFunc = MifareUltralightGetAtqa,
        .ApplicationSetAtqaFunc = MifareUltralightSetAtqa,
        .UidSize = MIFARE_ULTRALIGHT_UID_SIZE,
        .MemorySize = MIFARE_ULTRALIGHT_EV12_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
#ifdef CONFIG_MF_CLASSIC_MINI_4B_SUPPORT
    [CONFIG_MF_CLASSIC_MINI_4B] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareClassicAppInitMini4B,
        .ApplicationResetFunc = MifareClassicAppReset,
        .ApplicationTaskFunc = MifareClassicAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareClassicAppProcess,
        .ApplicationGetUidFunc = MifareClassicGetUid,
        .ApplicationSetUidFunc = MifareClassicSetUid,
        .ApplicationGetSakFunc = MifareClassicGetSak,
        .ApplicationSetSakFunc = MifareClassicSetSak,
        .ApplicationGetAtqaFunc = MifareClassicGetAtqa,
        .ApplicationSetAtqaFunc = MifareClassicSetAtqa,
        .UidSize = MIFARE_CLASSIC_UID_SIZE,
        .MemorySize = MIFARE_CLASSIC_MINI_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
#ifdef CONFIG_MF_CLASSIC_1K_SUPPORT
    [CONFIG_MF_CLASSIC_1K] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareClassicAppInit1K,
        .ApplicationResetFunc = MifareClassicAppReset,
        .ApplicationTaskFunc = MifareClassicAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareClassicAppProcess,
        .ApplicationGetUidFunc = MifareClassicGetUid,
        .ApplicationSetUidFunc = MifareClassicSetUid,
        .ApplicationGetSakFunc = MifareClassicGetSak,
        .ApplicationSetSakFunc = MifareClassicSetSak,
        .ApplicationGetAtqaFunc = MifareClassicGetAtqa,
        .ApplicationSetAtqaFunc = MifareClassicSetAtqa,
        .UidSize = MIFARE_CLASSIC_UID_SIZE,
        .MemorySize = MIFARE_CLASSIC_1K_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
#ifdef CONFIG_MF_CLASSIC_1K_7B_SUPPORT
    [CONFIG_MF_CLASSIC_1K_7B] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareClassicAppInit1K7B,
        .ApplicationResetFunc = MifareClassicAppReset,
        .ApplicationTaskFunc = MifareClassicAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareClassicAppProcess,
        .ApplicationGetUidFunc = MifareClassicGetUid,
        .ApplicationSetUidFunc = MifareClassicSetUid,
        .ApplicationGetSakFunc = MifareClassicGetSak,
        .ApplicationSetSakFunc = MifareClassicSetSak,
        .ApplicationGetAtqaFunc = MifareClassicGetAtqa,
        .ApplicationSetAtqaFunc = MifareClassicSetAtqa,
        .UidSize = ISO14443A_UID_SIZE_DOUBLE,
        .MemorySize = MIFARE_CLASSIC_1K_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
#ifdef CONFIG_MF_CLASSIC_4K_SUPPORT
    [CONFIG_MF_CLASSIC_4K] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareClassicAppInit4K,
        .ApplicationResetFunc = MifareClassicAppReset,
        .ApplicationTaskFunc = MifareClassicAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareClassicAppProcess,
        .ApplicationGetUidFunc = MifareClassicGetUid,
        .ApplicationSetUidFunc = MifareClassicSetUid,
        .ApplicationGetSakFunc = MifareClassicGetSak,
        .ApplicationSetSakFunc = MifareClassicSetSak,
        .ApplicationGetAtqaFunc = MifareClassicGetAtqa,
        .ApplicationSetAtqaFunc = MifareClassicSetAtqa,
        .UidSize = MIFARE_CLASSIC_UID_SIZE,
        .MemorySize = MIFARE_CLASSIC_4K_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
#ifdef CONFIG_MF_CLASSIC_4K_7B_SUPPORT
    [CONFIG_MF_CLASSIC_4K_7B] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareClassicAppInit4K7B,
        .ApplicationResetFunc = MifareClassicAppReset,
        .ApplicationTaskFunc = MifareClassicAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareClassicAppProcess,
        .ApplicationGetUidFunc = MifareClassicGetUid,
        .ApplicationSetUidFunc = MifareClassicSetUid,
        .ApplicationGetSakFunc = MifareClassicGetSak,
        .ApplicationSetSakFunc = MifareClassicSetSak,
        .ApplicationGetAtqaFunc = MifareClassicGetAtqa,
        .ApplicationSetAtqaFunc = MifareClassicSetAtqa,
        .UidSize = ISO14443A_UID_SIZE_DOUBLE,
        .MemorySize = MIFARE_CLASSIC_4K_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
#ifdef CONFIG_MF_DETECTION_SUPPORT
    [CONFIG_MF_DETECTION] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareDetectionInit1K,
        .ApplicationResetFunc = MifareClassicAppReset,
        .ApplicationTaskFunc = MifareClassicAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareClassicAppProcess,
        .ApplicationGetUidFunc = MifareClassicGetUid,
        .ApplicationSetUidFunc = MifareClassicSetUid,
        .ApplicationGetSakFunc = MifareClassicGetSak,
        .ApplicationSetSakFunc = MifareClassicSetSak,
        .ApplicationGetAtqaFunc = MifareClassicGetAtqa,
        .ApplicationSetAtqaFunc = MifareClassicSetAtqa,
        .UidSize = MIFARE_CLASSIC_UID_SIZE,
        .MemorySize = MIFARE_CLASSIC_1K_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
#ifdef CONFIG_MF_DETECTION_4K_SUPPORT
    [CONFIG_MF_DETECTION_4K] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = MifareDetectionInit4K,
        .ApplicationResetFunc = MifareClassicAppReset,
        .ApplicationTaskFunc = MifareClassicAppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = MifareClassicAppProcess,
        .ApplicationGetUidFunc = MifareClassicGetUid,
        .ApplicationSetUidFunc = MifareClassicSetUid,
        .ApplicationGetSakFunc = MifareClassicGetSak,
        .ApplicationSetSakFunc = MifareClassicSetSak,
        .ApplicationGetAtqaFunc = MifareClassicGetAtqa,
        .ApplicationSetAtqaFunc = MifareClassicSetAtqa,
        .UidSize = MIFARE_CLASSIC_UID_SIZE,
        .MemorySize = MIFARE_CLASSIC_4K_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
#ifdef CONFIG_ISO14443A_SNIFF_SUPPORT
    [CONFIG_ISO14443A_SNIFF] = {
        .CodecInitFunc = Sniff14443ACodecInit,
        .CodecDeInitFunc = Sniff14443ACodecDeInit,
        .CodecTaskFunc = Sniff14443ACodecTask,
        .ApplicationInitFunc = Sniff14443AAppInit,
        .ApplicationResetFunc = Sniff14443AAppReset,
        .ApplicationTaskFunc = Sniff14443AAppTask,
        .ApplicationTickFunc = Sniff14443AAppTick,
        .ApplicationProcessFunc = Sniff14443AAppProcess,
        .ApplicationGetUidFunc = ApplicationGetUidDummy,
        .ApplicationSetUidFunc = ApplicationSetUidDummy,
        .ApplicationGetSakFunc = ApplicationGetSakDummy,
        .ApplicationSetSakFunc = ApplicationSetSakDummy,
        .ApplicationGetAtqaFunc = ApplicationGetAtqaDummy,
        .ApplicationSetAtqaFunc = ApplicationSetAtqaDummy,
        .UidSize = 0,
        .MemorySize = 0,
        .ReadOnly = true,
        .TagFamily = TAG_FAMILY_NONE
    },
#endif
#ifdef CONFIG_ISO14443A_READER_SUPPORT
    [CONFIG_ISO14443A_READER] = {
        .CodecInitFunc = Reader14443ACodecInit,
        .CodecDeInitFunc = Reader14443ACodecDeInit,
        .CodecTaskFunc = Reader14443ACodecTask,
        .ApplicationInitFunc = Reader14443AAppInit,
        .ApplicationResetFunc = Reader14443AAppReset,
        .ApplicationTaskFunc = Reader14443AAppTask,
        .ApplicationTickFunc = Reader14443AAppTick,
        .ApplicationProcessFunc = Reader14443AAppProcess,
        .ApplicationGetUidFunc = ApplicationGetUidDummy,
        .ApplicationSetUidFunc = ApplicationSetUidDummy,
        .ApplicationGetSakFunc = ApplicationGetSakDummy,
        .ApplicationSetSakFunc = ApplicationSetSakDummy,
        .ApplicationGetAtqaFunc = ApplicationGetAtqaDummy,
        .ApplicationSetAtqaFunc = ApplicationSetAtqaDummy,
        .UidSize = 0,
        .MemorySize = 0,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_NONE
    },
#endif
#ifdef CONFIG_VICINITY_SUPPORT
    [CONFIG_VICINITY] = {
        .CodecInitFunc = ISO15693CodecInit,
        .CodecDeInitFunc = ISO15693CodecDeInit,
        .CodecTaskFunc = ISO15693CodecTask,
        .ApplicationInitFunc = VicinityAppInit,
        .ApplicationResetFunc = VicinityAppReset,
        .ApplicationTaskFunc = VicinityAppTask,
        .ApplicationTickFunc = VicinityAppTick,
        .ApplicationProcessFunc = VicinityAppProcess,
        .ApplicationGetUidFunc = VicinityGetUid,
        .ApplicationSetUidFunc = VicinitySetUid,
        .UidSize = ISO15693_GENERIC_UID_SIZE,
        .MemorySize = ISO15693_GENERIC_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO15693
    },
#endif
#ifdef CONFIG_ISO15693_SNIFF_SUPPORT
    [CONFIG_ISO15693_SNIFF] = {
        .CodecInitFunc = ISO15693CodecInit,
        .CodecDeInitFunc = ISO15693CodecDeInit,
        .CodecTaskFunc = ISO15693CodecTask,
        .ApplicationInitFunc = ApplicationInitDummy,
        .ApplicationResetFunc = ApplicationResetDummy,
        .ApplicationTaskFunc = ApplicationTaskDummy,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = ApplicationProcessDummy,
        .ApplicationGetUidFunc = ApplicationGetUidDummy,
        .ApplicationSetUidFunc = ApplicationSetUidDummy,
        .UidSize = 0,
        .MemorySize = 0,
        .ReadOnly = true,
        .TagFamily = TAG_FAMILY_NONE
    },
#endif
#ifdef CONFIG_SL2S2002_SUPPORT
    [CONFIG_SL2S2002] = {
        .CodecInitFunc = ISO15693CodecInit,
        .CodecDeInitFunc = ISO15693CodecDeInit,
        .CodecTaskFunc = ISO15693CodecTask,
        .ApplicationInitFunc = Sl2s2002AppInit,
        .ApplicationResetFunc = Sl2s2002AppReset,
        .ApplicationTaskFunc = Sl2s2002AppTask,
        .ApplicationTickFunc = Sl2s2002AppTick,
        .ApplicationProcessFunc = Sl2s2002AppProcess,
        .ApplicationGetUidFunc = Sl2s2002GetUid,
        .ApplicationSetUidFunc = Sl2s2002SetUid,
        .UidSize = ISO15693_GENERIC_UID_SIZE,
        .MemorySize = ISO15693_GENERIC_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO15693
    },
#endif
#ifdef CONFIG_TITAGITSTANDARD_SUPPORT
    [CONFIG_TITAGITSTANDARD] = {
        .CodecInitFunc = ISO15693CodecInit,
        .CodecDeInitFunc = ISO15693CodecDeInit,
        .CodecTaskFunc = ISO15693CodecTask,
        .ApplicationInitFunc = TITagitstandardAppInit,
        .ApplicationResetFunc = TITagitstandardAppReset,
        .ApplicationTaskFunc = TITagitstandardAppTask,
        .ApplicationTickFunc = TITagitstandardAppTick,
        .ApplicationProcessFunc = TITagitstandardAppProcess,
        .ApplicationGetUidFunc = TITagitstandardGetUid,
        .ApplicationSetUidFunc = TITagitstandardSetUid,
        .UidSize = TITAGIT_STD_UID_SIZE,
        .MemorySize = TITAGIT_STD_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO15693
    },
#endif
#ifdef CONFIG_EM4233_SUPPORT
    [CONFIG_EM4233] = {
        .CodecInitFunc = ISO15693CodecInit,
        .CodecDeInitFunc = ISO15693CodecDeInit,
        .CodecTaskFunc = ISO15693CodecTask,
        .ApplicationInitFunc = EM4233AppInit,
        .ApplicationResetFunc = EM4233AppReset,
        .ApplicationTaskFunc = EM4233AppTask,
        .ApplicationTickFunc = EM4233AppTick,
        .ApplicationProcessFunc = EM4233AppProcess,
        .ApplicationGetUidFunc = EM4233GetUid,
        .ApplicationSetUidFunc = EM4233SetUid,
        .UidSize = EM4233_STD_UID_SIZE,
        .MemorySize = EM4233_STD_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO15693
    },
#endif
#ifdef CONFIG_NTAG215_SUPPORT
    [CONFIG_NTAG215] = {
        .CodecInitFunc = ISO14443ACodecInit,
        .CodecDeInitFunc = ISO14443ACodecDeInit,
        .CodecTaskFunc = ISO14443ACodecTask,
        .ApplicationInitFunc = NTAG215AppInit,
        .ApplicationResetFunc = NTAG215AppReset,
        .ApplicationTaskFunc = NTAG215AppTask,
        .ApplicationTickFunc = ApplicationTickDummy,
        .ApplicationProcessFunc = NTAG215AppProcess,
        .ApplicationGetUidFunc = NTAG215GetUid,
        .ApplicationSetUidFunc = NTAG215SetUid,
        .UidSize = NTAG215_UID_SIZE,
        .MemorySize = NTAG215_MEM_SIZE,
        .ReadOnly = false,
        .TagFamily = TAG_FAMILY_ISO14443A
    },
#endif
};

ConfigurationType ActiveConfiguration;

void ConfigurationInit(void) {
    memcpy_P(&ActiveConfiguration,
             &ConfigurationTable[CONFIG_NONE], sizeof(ConfigurationType));
    //    Simulation mode antenna load, Default is close load.
    PORTC.DIRSET = PIN7_bm;
    PORTC.OUTCLR = PIN7_bm;

    ConfigurationSetById(GlobalSettings.ActiveSettingPtr->Configuration);
}

void ConfigurationSetById(ConfigurationEnum Configuration) {
    CodecDeInit();

    //    Cancel currently executed command when configuration changes
    CommandLinePendingTaskBreak(); // break possibly pending task

    GlobalSettings.ActiveSettingPtr->Configuration = Configuration;

    /* Copy struct from PROGMEM to RAM */
    memcpy_P(&ActiveConfiguration,
             &ConfigurationTable[Configuration], sizeof(ConfigurationType));

    //    Configure antenna load as appropriate
#ifdef CONFIG_ISO14443A_READER_SUPPORT
    if (Configuration == CONFIG_ISO14443A_READER)
        PORTC.OUTCLR = PIN7_bm;
    else
        PORTC.OUTSET = PIN7_bm;
#else
    PORTC.OUTSET = PIN7_bm;
#endif

    CodecInit();
    ApplicationInit();
}

void ConfigurationGetByName(char *Configuration, uint16_t BufferSize) {
    MapIdToText(ConfigurationMap, ARRAY_COUNT(ConfigurationMap), GlobalSettings.ActiveSettingPtr->Configuration, Configuration, BufferSize);
}

bool ConfigurationSetByName(const char *Configuration) {
    MapIdType Id;

    if (MapTextToId(ConfigurationMap, ARRAY_COUNT(ConfigurationMap), Configuration, &Id)) {
        //    The last configuration can only be configured as a reader
#ifdef CONFIG_ISO14443A_READER_SUPPORT
        if (GlobalSettings.ActiveSettingIdx >= SETTINGS_COUNT && Id != CONFIG_ISO14443A_READER) {
#else
        if (GlobalSettings.ActiveSettingIdx >= SETTINGS_COUNT) {
#endif
            return false;
        }
        ConfigurationSetById(Id);
        LogEntry(LOG_INFO_CONFIG_SET, Configuration, StringLength(Configuration, CONFIGURATION_NAME_LENGTH_MAX - 1));
        return true;
    } else {
        return false;
    }
}

void ConfigurationGetList(char *List, uint16_t BufferSize) {
    MapToString(ConfigurationMap, ARRAY_COUNT(ConfigurationMap), List, BufferSize);
}



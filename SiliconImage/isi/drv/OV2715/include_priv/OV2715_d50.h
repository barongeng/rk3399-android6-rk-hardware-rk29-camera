/******************************************************************************
 *
 * Copyright 2010, Dream Chip Technologies GmbH. All rights reserved.
 * No part of this work may be reproduced, modified, distributed, transmitted,
 * transcribed, or translated into any language or computer format, in any form
 * or by any means without written permission of:
 * Dream Chip Technologies GmbH, Steinriede 10, 30827 Garbsen / Berenbostel,
 * Germany
 *
 *****************************************************************************/
/**
 * @file isi_iss.h
 *
 * @brief Interface description for image sensor specific implementation (iss).
 *
 *****************************************************************************/
/**
 * @page module_name_page Module Name
 * Describe here what this module does.
 *
 * For a detailed list of functions and implementation detail refer to:
 * - @ref module_name
 *
 * @defgroup ov5630_d50   Illumination Profile D50
 * @{
 *
 */
#ifndef __OV2715_D50_H__
#define __OV2715_D50_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define AWB_COLORMATRIX_ARRAY_SIZE_CIE_D50  2
#define AWB_LSCMATRIX_ARRAY_SIZE_CIE_D50    1

#define AWB_SATURATION_ARRAY_SIZE_CIE_D50   4
#define AWB_VIGNETTING_ARRAY_SIZE_CIE_D50   2

/*****************************************************************************/
/*!
 * Sunny Outdoor Profile of sunny daylight
 *  color temperature was ~5000 Kelvin during measurement
 */
/*****************************************************************************/

// crosstalk matrix
const Isi3x3FloatMatrix_t  OV2715_XTalkCoeff_D50 =
{
    {
         1.51662f,  -0.25372f,  -0.26290f, 
        -0.29235f,   1.95046f,  -0.65811f, 
        -0.15629f,  -1.33599f,   2.49228f  
    }
};

// crosstalk offset matrix
const IsiXTalkFloatOffset_t OV2715_XTalkOffset_D50 =
{
    .fCtOffsetRed      = (-127.0625f / CC_OFFSET_SCALING),
    .fCtOffsetGreen    = (-126.6875f / CC_OFFSET_SCALING),
    .fCtOffsetBlue     = (-121.5625f / CC_OFFSET_SCALING)
};

// gain matrix
const IsiComponentGain_t OV2715_CompGain_D50 =
{
    .fRed      = 1.16870f,
    .fGreenR   = 1.00000f,
    .fGreenB   = 1.00000f,
    .fBlue     = 1.69912f
};

// mean value of gaussian mixture model
const Isi2x1FloatMatrix_t OV2715_GaussMeanValue_D50 =
{
    {
        -0.03923f,  0.02969f
    }
};

// inverse covariance matrix
const Isi2x2FloatMatrix_t OV2715_CovarianceMatrix_D50 =
{
    {
        943.31271f,  -803.83137f, 
       -803.83137f,  2446.16561f 
    }
};

// factor in gaussian mixture model
const IsiGaussFactor_t OV2715_GaussFactor_D50 =
{
    .fGaussFactor = 205.14043f
};

// thresholds for switching between MAP classification and interpolation
const Isi2x1FloatMatrix_t OV2715_Threshold_D50 =
{
    {
        1.0f, 1.0f // 1 = disabled
    }
};

// saturation curve
float afSaturationSensorGain_D50[AWB_SATURATION_ARRAY_SIZE_CIE_D50] =
{
    1.0f, 2.0f, 4.0f, 8.0f
};

float afSaturation_D50[AWB_SATURATION_ARRAY_SIZE_CIE_D50] =
{
    100.0f, 100.0f, 90.0f, 74.0f
};

const IsiSaturationCurve_t OV2715_SaturationCurve_D50 =
{
    .ArraySize      = AWB_SATURATION_ARRAY_SIZE_CIE_D50,
    .pSensorGain    = &afSaturationSensorGain_D50[0],
    .pSaturation    = &afSaturation_D50[0]
};

// saturation depended color conversion matrices
IsiSatCcMatrix_t OV2715_SatCcMatrix_D50[AWB_COLORMATRIX_ARRAY_SIZE_CIE_D50] =
{
    {
        .fSaturation    = 74.0f,
        .XTalkCoeff     =
        {
            {
                1.42364f,  -0.24767f,  -0.17597f, 
                0.12842f,   1.30456f,  -0.43298f, 
                0.24046f,  -1.05459f,   1.81413f  
            }
        }
    },
    {
        .fSaturation    = 100.0f,
        .XTalkCoeff     =
        {
            {
                1.51662f,  -0.25372f,  -0.26290f, 
               -0.29235f,   1.95046f,  -0.65811f, 
               -0.15629f,  -1.33599f,   2.49228f  
            }
        }
    }
};

const IsiCcMatrixTable_t OV2715_CcMatrixTable_D50 =
{
    .ArraySize          = AWB_COLORMATRIX_ARRAY_SIZE_CIE_D50,
    .pIsiSatCcMatrix    = &OV2715_SatCcMatrix_D50[0]
};

// saturation depended color conversion offset vectors
IsiSatCcOffset_t OV2715_SatCcOffset_D50[AWB_COLORMATRIX_ARRAY_SIZE_CIE_D50] =
{
    {
        .fSaturation    = 74.0f,
        .CcOffset       =
        {
            .fCtOffsetRed   = 0.0f,
            .fCtOffsetGreen = 0.0f,
            .fCtOffsetBlue  = 0.0f
        }
    },
    {
        .fSaturation    = 100.0f,
        .CcOffset       =
        {
            .fCtOffsetRed      = (-127.0625f / CC_OFFSET_SCALING),
            .fCtOffsetGreen    = (-126.6875f / CC_OFFSET_SCALING),
            .fCtOffsetBlue     = (-121.5625f / CC_OFFSET_SCALING)
        }
    }
};

const IsiCcOffsetTable_t OV2715_CcOffsetTable_D50=
{
    .ArraySize          = AWB_COLORMATRIX_ARRAY_SIZE_CIE_D50,
    .pIsiSatCcOffset    = &OV2715_SatCcOffset_D50[0]
};

// vignetting curve
float afVignettingSensorGain_D50[AWB_VIGNETTING_ARRAY_SIZE_CIE_D50] =
{
    1.0f, 8.0f
};

float afVignetting_D50[AWB_VIGNETTING_ARRAY_SIZE_CIE_D50] =
{
    100.0f, 100.0f
};

const IsiVignettingCurve_t OV2715_VignettingCurve_D50 =
{
    .ArraySize      = AWB_VIGNETTING_ARRAY_SIZE_CIE_D50,
    .pSensorGain    = &afVignettingSensorGain_D50[0],
    .pVignetting    = &afVignetting_D50[0]
};

// vignetting dependend lsc matrices
IsiVignLscMatrix_t OV2715_VignLscMatrix_CIE_D50_1920x1080[AWB_LSCMATRIX_ARRAY_SIZE_CIE_D50] = 
{
    // array item 0
    {
       .fVignetting    = 100.0f,
       .LscMatrix      =
       {
           // ISI_COLOR_COMPONENT_RED
           {
               {
                    1145U, 1117U, 1103U, 1084U, 1069U, 1058U, 1053U, 1048U, 1036U, 1037U, 1035U, 1034U, 1038U, 1044U, 1046U, 1059U, 1071U,
                    1144U, 1120U, 1105U, 1084U, 1068U, 1062U, 1056U, 1045U, 1044U, 1035U, 1035U, 1035U, 1035U, 1040U, 1048U, 1057U, 1068U,
                    1139U, 1119U, 1101U, 1085U, 1069U, 1064U, 1056U, 1049U, 1042U, 1036U, 1034U, 1032U, 1031U, 1037U, 1044U, 1055U, 1061U,
                    1138U, 1113U, 1098U, 1086U, 1071U, 1060U, 1057U, 1048U, 1041U, 1034U, 1033U, 1030U, 1029U, 1033U, 1038U, 1052U, 1051U,
                    1130U, 1118U, 1098U, 1083U, 1069U, 1062U, 1057U, 1045U, 1037U, 1038U, 1031U, 1031U, 1028U, 1033U, 1033U, 1045U, 1051U,
                    1137U, 1116U, 1100U, 1084U, 1072U, 1062U, 1055U, 1045U, 1039U, 1032U, 1033U, 1031U, 1028U, 1028U, 1032U, 1045U, 1046U,
                    1136U, 1118U, 1100U, 1084U, 1074U, 1063U, 1053U, 1040U, 1035U, 1031U, 1029U, 1030U, 1025U, 1031U, 1032U, 1042U, 1043U,
                    1137U, 1120U, 1099U, 1087U, 1073U, 1063U, 1053U, 1040U, 1028U, 1028U, 1028U, 1028U, 1027U, 1026U, 1028U, 1041U, 1041U,
                    1143U, 1119U, 1100U, 1088U, 1076U, 1063U, 1051U, 1041U, 1027U, 1027U, 1027U, 1027U, 1028U, 1025U, 1029U, 1035U, 1045U,
                    1144U, 1122U, 1103U, 1087U, 1077U, 1066U, 1055U, 1042U, 1029U, 1027U, 1028U, 1027U, 1024U, 1028U, 1026U, 1036U, 1036U,
                    1143U, 1125U, 1107U, 1093U, 1074U, 1067U, 1052U, 1042U, 1034U, 1029U, 1027U, 1030U, 1027U, 1027U, 1026U, 1036U, 1045U,
                    1148U, 1127U, 1111U, 1090U, 1077U, 1065U, 1058U, 1042U, 1035U, 1030U, 1029U, 1029U, 1027U, 1024U, 1027U, 1043U, 1041U,
                    1155U, 1134U, 1111U, 1093U, 1079U, 1064U, 1057U, 1044U, 1040U, 1031U, 1030U, 1027U, 1030U, 1027U, 1030U, 1040U, 1051U,
                    1157U, 1139U, 1117U, 1096U, 1077U, 1068U, 1054U, 1047U, 1040U, 1032U, 1029U, 1030U, 1027U, 1027U, 1032U, 1044U, 1046U,
                    1166U, 1143U, 1121U, 1095U, 1081U, 1071U, 1061U, 1047U, 1040U, 1031U, 1029U, 1030U, 1027U, 1030U, 1036U, 1049U, 1050U,
                    1174U, 1145U, 1121U, 1103U, 1085U, 1071U, 1058U, 1047U, 1038U, 1034U, 1029U, 1029U, 1028U, 1031U, 1040U, 1049U, 1055U,
                    1172U, 1143U, 1126U, 1106U, 1091U, 1071U, 1062U, 1047U, 1040U, 1031U, 1027U, 1031U, 1029U, 1039U, 1043U, 1053U, 1074U
               }
           }, 
    
           // ISI_COLOR_COMPONENT_GREENR
           {
               {
                    1108U, 1095U, 1080U, 1072U, 1059U, 1057U, 1051U, 1052U, 1044U, 1036U, 1031U, 1027U, 1024U, 1031U, 1036U, 1048U, 1059U,
                    1127U, 1101U, 1090U, 1080U, 1071U, 1074U, 1069U, 1064U, 1056U, 1051U, 1043U, 1037U, 1035U, 1037U, 1043U, 1060U, 1069U,
                    1123U, 1100U, 1089U, 1078U, 1073U, 1070U, 1071U, 1069U, 1064U, 1054U, 1046U, 1040U, 1035U, 1035U, 1042U, 1055U, 1056U,
                    1117U, 1103U, 1085U, 1077U, 1071U, 1072U, 1070U, 1072U, 1065U, 1061U, 1048U, 1043U, 1037U, 1036U, 1038U, 1048U, 1052U,
                    1122U, 1103U, 1092U, 1079U, 1070U, 1070U, 1074U, 1073U, 1068U, 1062U, 1054U, 1046U, 1039U, 1036U, 1034U, 1044U, 1044U,
                    1123U, 1104U, 1087U, 1083U, 1075U, 1075U, 1069U, 1071U, 1067U, 1063U, 1059U, 1051U, 1039U, 1034U, 1035U, 1039U, 1043U,
                    1124U, 1109U, 1093U, 1081U, 1076U, 1072U, 1071U, 1068U, 1066U, 1067U, 1059U, 1049U, 1041U, 1037U, 1031U, 1038U, 1039U,
                    1127U, 1112U, 1094U, 1085U, 1078U, 1074U, 1070U, 1068U, 1061U, 1063U, 1057U, 1051U, 1042U, 1033U, 1034U, 1041U, 1041U,
                    1132U, 1111U, 1098U, 1085U, 1080U, 1078U, 1071U, 1068U, 1059U, 1060U, 1055U, 1050U, 1043U, 1040U, 1036U, 1038U, 1039U,
                    1137U, 1118U, 1100U, 1091U, 1081U, 1080U, 1072U, 1067U, 1061U, 1059U, 1055U, 1054U, 1046U, 1041U, 1034U, 1038U, 1036U,
                    1141U, 1122U, 1104U, 1093U, 1085U, 1081U, 1071U, 1066U, 1059U, 1060U, 1058U, 1057U, 1052U, 1041U, 1033U, 1036U, 1041U,
                    1143U, 1127U, 1112U, 1099U, 1084U, 1078U, 1071U, 1062U, 1062U, 1059U, 1061U, 1055U, 1051U, 1041U, 1036U, 1044U, 1040U,
                    1150U, 1136U, 1116U, 1097U, 1088U, 1077U, 1067U, 1065U, 1062U, 1060U, 1055U, 1055U, 1049U, 1045U, 1039U, 1046U, 1044U,
                    1160U, 1139U, 1116U, 1102U, 1082U, 1074U, 1071U, 1066U, 1063U, 1057U, 1053U, 1053U, 1051U, 1048U, 1046U, 1049U, 1047U,
                    1163U, 1142U, 1121U, 1098U, 1090U, 1081U, 1074U, 1066U, 1061U, 1054U, 1051U, 1055U, 1052U, 1051U, 1050U, 1057U, 1051U,
                    1173U, 1141U, 1120U, 1109U, 1095U, 1083U, 1076U, 1063U, 1060U, 1055U, 1055U, 1055U, 1055U, 1054U, 1056U, 1058U, 1059U,
                    1163U, 1140U, 1132U, 1115U, 1097U, 1082U, 1071U, 1067U, 1059U, 1059U, 1058U, 1056U, 1055U, 1061U, 1059U, 1062U, 1069U
               },
           },
    
           // ISI_COLOR_COMPONENT_GREENB
           {
               {
                    1113U, 1096U, 1083U, 1075U, 1060U, 1058U, 1053U, 1052U, 1045U, 1037U, 1031U, 1028U, 1024U, 1031U, 1035U, 1048U, 1058U, 
                    1130U, 1104U, 1092U, 1082U, 1072U, 1077U, 1068U, 1066U, 1058U, 1051U, 1042U, 1037U, 1035U, 1037U, 1044U, 1057U, 1069U,
                    1126U, 1104U, 1091U, 1080U, 1075U, 1071U, 1072U, 1068U, 1065U, 1055U, 1046U, 1039U, 1035U, 1036U, 1043U, 1055U, 1058U,
                    1122U, 1106U, 1089U, 1079U, 1072U, 1072U, 1073U, 1072U, 1066U, 1059U, 1050U, 1043U, 1037U, 1037U, 1037U, 1049U, 1049U,
                    1124U, 1106U, 1093U, 1082U, 1072U, 1074U, 1075U, 1075U, 1069U, 1063U, 1053U, 1047U, 1038U, 1034U, 1036U, 1042U, 1047U,
                    1128U, 1107U, 1091U, 1084U, 1077U, 1075U, 1070U, 1071U, 1069U, 1064U, 1061U, 1050U, 1042U, 1034U, 1034U, 1041U, 1042U,
                    1129U, 1110U, 1095U, 1084U, 1078U, 1076U, 1072U, 1070U, 1066U, 1068U, 1058U, 1052U, 1041U, 1037U, 1032U, 1039U, 1041U,
                    1129U, 1116U, 1096U, 1089U, 1079U, 1075U, 1071U, 1069U, 1062U, 1064U, 1059U, 1051U, 1043U, 1036U, 1034U, 1041U, 1043U,
                    1138U, 1116U, 1099U, 1089U, 1080U, 1079U, 1072U, 1069U, 1061U, 1059U, 1055U, 1051U, 1043U, 1040U, 1035U, 1040U, 1041U,
                    1141U, 1120U, 1103U, 1092U, 1082U, 1082U, 1074U, 1068U, 1062U, 1059U, 1055U, 1055U, 1047U, 1042U, 1036U, 1039U, 1036U,
                    1145U, 1127U, 1107U, 1096U, 1088U, 1081U, 1071U, 1068U, 1061U, 1061U, 1059U, 1057U, 1052U, 1042U, 1031U, 1039U, 1042U,
                    1147U, 1130U, 1114U, 1100U, 1087U, 1080U, 1074U, 1063U, 1062U, 1060U, 1061U, 1057U, 1052U, 1042U, 1036U, 1045U, 1041U,
                    1155U, 1139U, 1118U, 1101U, 1089U, 1080U, 1068U, 1067U, 1064U, 1061U, 1055U, 1056U, 1051U, 1045U, 1042U, 1049U, 1045U,
                    1165U, 1140U, 1120U, 1104U, 1085U, 1074U, 1073U, 1067U, 1061U, 1060U, 1052U, 1055U, 1050U, 1049U, 1046U, 1050U, 1050U,
                    1167U, 1147U, 1123U, 1099U, 1091U, 1082U, 1074U, 1067U, 1062U, 1054U, 1053U, 1055U, 1052U, 1050U, 1050U, 1057U, 1051U,
                    1177U, 1143U, 1123U, 1111U, 1096U, 1085U, 1077U, 1064U, 1062U, 1055U, 1057U, 1055U, 1057U, 1055U, 1057U, 1059U, 1059U,
                    1165U, 1145U, 1133U, 1117U, 1098U, 1084U, 1072U, 1067U, 1062U, 1058U, 1058U, 1056U, 1057U, 1060U, 1061U, 1063U, 1070U
               },
           },
    
           // ISI_COLOR_COMPONENT_BLUE
           {
               {
                    1069U, 1061U, 1051U, 1046U, 1031U, 1037U, 1035U, 1036U, 1039U, 1028U, 1025U, 1028U, 1024U, 1028U, 1028U, 1039U, 1046U,
                    1086U, 1072U, 1059U, 1059U, 1049U, 1053U, 1050U, 1055U, 1047U, 1049U, 1038U, 1038U, 1032U, 1032U, 1040U, 1044U, 1049U,
                    1088U, 1069U, 1061U, 1055U, 1051U, 1054U, 1058U, 1055U, 1057U, 1048U, 1044U, 1038U, 1034U, 1033U, 1035U, 1041U, 1046U,
                    1089U, 1071U, 1060U, 1053U, 1056U, 1054U, 1058U, 1061U, 1058U, 1053U, 1050U, 1045U, 1034U, 1035U, 1035U, 1039U, 1041U,
                    1084U, 1068U, 1062U, 1054U, 1055U, 1059U, 1065U, 1063U, 1060U, 1060U, 1053U, 1042U, 1042U, 1032U, 1029U, 1037U, 1029U,
                    1078U, 1071U, 1060U, 1056U, 1059U, 1060U, 1064U, 1057U, 1059U, 1059U, 1053U, 1048U, 1037U, 1032U, 1028U, 1034U, 1032U,
                    1088U, 1070U, 1063U, 1058U, 1057U, 1061U, 1062U, 1060U, 1057U, 1061U, 1052U, 1048U, 1038U, 1032U, 1024U, 1033U, 1032U,
                    1091U, 1073U, 1061U, 1059U, 1059U, 1061U, 1058U, 1059U, 1053U, 1055U, 1054U, 1045U, 1037U, 1028U, 1028U, 1035U, 1037U,
                    1093U, 1077U, 1066U, 1062U, 1063U, 1062U, 1064U, 1061U, 1049U, 1054U, 1050U, 1048U, 1041U, 1032U, 1032U, 1037U, 1029U,
                    1092U, 1080U, 1066U, 1064U, 1060U, 1068U, 1065U, 1057U, 1052U, 1052U, 1053U, 1051U, 1042U, 1037U, 1027U, 1033U, 1033U,
                    1092U, 1083U, 1071U, 1067U, 1066U, 1066U, 1062U, 1052U, 1049U, 1050U, 1052U, 1051U, 1049U, 1033U, 1027U, 1034U, 1034U,
                    1098U, 1084U, 1075U, 1067U, 1064U, 1061U, 1057U, 1052U, 1052U, 1052U, 1057U, 1056U, 1045U, 1036U, 1029U, 1038U, 1031U,
                    1098U, 1091U, 1075U, 1067U, 1058U, 1055U, 1052U, 1052U, 1055U, 1056U, 1051U, 1049U, 1045U, 1037U, 1031U, 1040U, 1034U,
                    1103U, 1088U, 1076U, 1063U, 1056U, 1051U, 1053U, 1060U, 1052U, 1051U, 1048U, 1048U, 1044U, 1038U, 1039U, 1043U, 1040U,
                    1098U, 1086U, 1072U, 1057U, 1053U, 1059U, 1059U, 1055U, 1049U, 1050U, 1048U, 1053U, 1047U, 1040U, 1041U, 1047U, 1041U,
                    1104U, 1078U, 1060U, 1063U, 1066U, 1060U, 1057U, 1058U, 1049U, 1051U, 1049U, 1050U, 1050U, 1046U, 1046U, 1048U, 1047U,
                    1073U, 1063U, 1071U, 1066U, 1057U, 1053U, 1047U, 1051U, 1052U, 1051U, 1045U, 1052U, 1050U, 1050U, 1052U, 1054U, 1064U
               },
           },
       },
    },
};

IsiLscMatrixTable_t OV2715_LscMatrixTable_CIE_D50_1920x1080 = 
{
    .ArraySize          = AWB_LSCMATRIX_ARRAY_SIZE_CIE_D50,
    .psIsiVignLscMatrix = &OV2715_VignLscMatrix_CIE_D50_1920x1080[0],
    .LscXGradTbl        = { 285U, 280U, 278U, 266U, 273U, 266U, 271U, 266U },
    .LscYGradTbl        = { 482U, 475U, 496U, 475U, 489U, 482U, 496U, 489U },
    .LscXSizeTbl        = { 115U, 117U, 118U, 123U, 120U, 123U, 121U, 123U },
    .LscYSizeTbl        = {  68U,  69U,  66U,  69U,  67U,  68U,  66U,  67U }
};



#ifdef __cplusplus
}
#endif

/* @} ov5630_d50 */

#endif /* __OV2715_D50_H__ */


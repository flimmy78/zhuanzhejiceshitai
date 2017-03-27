#ifndef _EXCEL_H
#define _EXCEL_H

#include <cviauto.h>

#ifdef __cplusplus
    extern "C" {
#endif
/* NICDBLD_BEGIN> ActiveX Automation Properties */

/* NICDBLD_BEGIN> Object Name: _Application */
#define Excel_App_Default                             0x00000000
#define Excel_AppUILanguage                           0x00000002
#define Excel_AppValue                                0x00000006
#define Excel_AppName                                 0x0000006E
#define Excel_AppCharts                               0x00000079
#define Excel_AppWidth                                0x0000007A
#define Excel_AppHeight                               0x0000007B
#define Excel_AppTop                                  0x0000007E
#define Excel_AppLeft                                 0x0000007F
#define Excel_AppCaption                              0x0000008B
#define Excel_AppSelection                            0x00000093
#define Excel_AppApplication                          0x00000094
#define Excel_AppCreator                              0x00000095
#define Excel_AppParent                               0x00000096
#define Excel_AppActiveChart                          0x000000B7
#define Excel_AppDefaultSheetDirection                0x000000E5
#define Excel_AppCursorMovement                       0x000000E8
#define Excel_AppControlCharacters                    0x000000E9
#define Excel_AppCells                                0x000000EE
#define Excel_AppColumns                              0x000000F1
#define Excel_AppRows                                 0x00000102
#define Excel_AppPath                                 0x00000123
#define Excel_AppActiveCell                           0x00000131
#define Excel_AppActivePrinter                        0x00000132
#define Excel_AppActiveSheet                          0x00000133
#define Excel_AppActiveWorkbook                       0x00000134
#define Excel_AppTransitionMenuKey                    0x00000136
#define Excel_AppTransitionMenuKeyAction              0x00000137
#define Excel_AppTransitionNavigKeys                  0x00000138
#define Excel_AppAltStartupPath                       0x00000139
#define Excel_AppBuild                                0x0000013A
#define Excel_AppCalculateBeforeSave                  0x0000013B
#define Excel_AppCalculation                          0x0000013C
#define Excel_AppCanPlaySounds                        0x0000013E
#define Excel_AppCanRecordSounds                      0x0000013F
#define Excel_AppCellDragAndDrop                      0x00000140
#define Excel_AppDisplayClipboardWindow               0x00000142
#define Excel_AppCommandUnderlines                    0x00000143
#define Excel_AppConstrainNumeric                     0x00000144
#define Excel_AppCutCopyMode                          0x0000014A
#define Excel_AppDataEntryMode                        0x0000014B
#define Excel_AppDDEAppReturnCode                     0x0000014C
#define Excel_AppDisplayAlerts                        0x00000157
#define Excel_AppDisplayFormulaBar                    0x00000158
#define Excel_AppDisplayNoteIndicator                 0x00000159
#define Excel_AppDisplayScrollBars                    0x0000015A
#define Excel_AppDisplayStatusBar                     0x0000015B
#define Excel_AppFixedDecimal                         0x0000015F
#define Excel_AppFixedDecimalPlaces                   0x00000160
#define Excel_AppIgnoreRemoteRequests                 0x00000164
#define Excel_AppInteractive                          0x00000169
#define Excel_AppIteration                            0x0000016B
#define Excel_AppLargeButtons                         0x0000016C
#define Excel_AppColorButtons                         0x0000016D
#define Excel_AppLibraryPath                          0x0000016E
#define Excel_AppMathCoprocessorAvailable             0x0000016F
#define Excel_AppMaxChange                            0x00000170
#define Excel_AppMaxIterations                        0x00000171
#define Excel_AppMemoryFree                           0x00000172
#define Excel_AppMemoryTotal                          0x00000173
#define Excel_AppMemoryUsed                           0x00000174
#define Excel_AppMouseAvailable                       0x00000175
#define Excel_AppMoveAfterReturn                      0x00000176
#define Excel_AppOperatingSystem                      0x00000177
#define Excel_AppOrganizationName                     0x00000178
#define Excel_AppPathSeparator                        0x00000179
#define Excel_AppRecordRelative                       0x0000017B
#define Excel_AppReferenceStyle                       0x0000017C
#define Excel_AppTemplatesPath                        0x0000017D
#define Excel_AppScreenUpdating                       0x0000017E
#define Excel_AppStartupPath                          0x00000181
#define Excel_AppStatusBar                            0x00000182
#define Excel_AppShowToolTips                         0x00000183
#define Excel_AppNetworkTemplatesPath                 0x00000184
#define Excel_AppUsableHeight                         0x00000185
#define Excel_AppUsableWidth                          0x00000186
#define Excel_AppUserName                             0x00000187
#define Excel_AppVersion                              0x00000188
#define Excel_AppWindowsForPens                       0x0000018B
#define Excel_AppWindowState                          0x0000018C
#define Excel_AppWindows                              0x000001AE
#define Excel_AppNames                                0x000001BA
#define Excel_AppSheets                               0x000001E5
#define Excel_AppWorksheets                           0x000001EE
#define Excel_AppAddIns                               0x00000225
#define Excel_AppToolbars                             0x00000228
#define Excel_AppVisible                              0x0000022E
#define Excel_AppWorkbooks                            0x0000023C
#define Excel_AppExcel4MacroSheets                    0x00000243
#define Excel_AppExcel4IntlMacroSheets                0x00000245
#define Excel_AppModules                              0x00000246
#define Excel_AppMenuBars                             0x0000024D
#define Excel_AppOnWindow                             0x0000026F
#define Excel_AppOnCalculate                          0x00000271
#define Excel_AppOnEntry                              0x00000273
#define Excel_AppOnDoubleClick                        0x00000274
#define Excel_AppOnData                               0x00000275
#define Excel_AppActiveMenuBar                        0x000002F6
#define Excel_AppActiveWindow                         0x000002F7
#define Excel_AppDialogs                              0x000002F9
#define Excel_AppDialogSheets                         0x000002FC
#define Excel_AppThisWorkbook                         0x0000030A
#define Excel_AppCustomListCount                      0x00000313
#define Excel_AppActiveDialog                         0x0000032F
#define Excel_AppStandardFont                         0x0000039C
#define Excel_AppStandardFontSize                     0x0000039D
#define Excel_AppDisplayRecentFiles                   0x0000039E
#define Excel_AppDisplayExcel4Menus                   0x0000039F
#define Excel_AppEditDirectlyInCell                   0x000003A1
#define Excel_AppAlertBeforeOverwriting               0x000003A2
#define Excel_AppMailSession                          0x000003AE
#define Excel_AppMailSystem                           0x000003CB
#define Excel_AppCopyObjectsWithCells                 0x000003DF
#define Excel_AppAskToUpdateLinks                     0x000003E0
#define Excel_AppSheetsInNewWorkbook                  0x000003E1
#define Excel_AppOnSheetActivate                      0x00000407
#define Excel_AppDefaultFilePath                      0x0000040E
#define Excel_AppDisplayFullScreen                    0x00000425
#define Excel_AppPromptForSummaryInfo                 0x00000426
#define Excel_AppEnableTipWizard                      0x00000428
#define Excel_AppOnSheetDeactivate                    0x00000439
#define Excel_AppEnableCancelKey                      0x00000448
#define Excel_AppMoveAfterReturnDirection             0x00000478
#define Excel_AppAutoCorrect                          0x00000479
#define Excel_AppCursor                               0x00000489
#define Excel_AppEnableAutoComplete                   0x0000049B
#define Excel_AppEnableAnimations                     0x0000049C
#define Excel_AppDisplayCommentIndicator              0x000004AC
#define Excel_AppEnableSound                          0x000004AD
#define Excel_AppFileSearch                           0x000004B0
#define Excel_AppFileFind                             0x000004B1
#define Excel_AppRecentFiles                          0x000004B2
#define Excel_AppODBCErrors                           0x000004B3
#define Excel_AppODBCTimeout                          0x000004B4
#define Excel_AppPivotTableSelection                  0x000004B5
#define Excel_AppRollZoom                             0x000004B6
#define Excel_AppShowChartTipNames                    0x000004B7
#define Excel_AppShowChartTipValues                   0x000004B8
#define Excel_AppDefaultSaveFormat                    0x000004B9
#define Excel_AppUserControl                          0x000004BA
#define Excel_AppVBE                                  0x000004BB
#define Excel_AppEnableEvents                         0x000004BC
#define Excel_AppDisplayInfoWindow                    0x000004BD
#define Excel_AppAssistant                            0x0000059E
#define Excel_AppCommandBars                          0x0000059F
#define Excel_AppWorksheetFunction                    0x000005A0
#define Excel_AppNewWorkbook                          0x0000061D
#define Excel_AppExtendList                           0x00000701
#define Excel_AppOLEDBErrors                          0x00000702
#define Excel_AppCOMAddIns                            0x00000704
#define Excel_AppDefaultWebOptions                    0x00000705
#define Excel_AppProductCode                          0x00000706
#define Excel_AppUserLibraryPath                      0x00000707
#define Excel_AppAutoPercentEntry                     0x00000708
#define Excel_AppLanguageSettings                     0x00000709
#define Excel_AppDummy101                             0x0000070A
#define Excel_AppAnswerWizard                         0x0000070C
#define Excel_AppCalculationVersion                   0x0000070E
#define Excel_AppShowWindowsInTaskbar                 0x0000070F
#define Excel_AppFeatureInstall                       0x00000710
#define Excel_AppDecimalSeparator                     0x00000711
#define Excel_AppThousandsSeparator                   0x00000712
#define Excel_AppReady                                0x0000078C
#define Excel_AppFindFormat                           0x0000078E
#define Excel_AppReplaceFormat                        0x0000078F
#define Excel_AppUsedObjects                          0x00000790
#define Excel_AppCalculationState                     0x00000791
#define Excel_AppCalculationInterruptKey              0x00000792
#define Excel_AppWatches                              0x00000793
#define Excel_AppDisplayFunctionToolTips              0x00000794
#define Excel_AppAutomationSecurity                   0x00000795
#define Excel_AppDisplayPasteOptions                  0x0000079A
#define Excel_AppDisplayInsertOptions                 0x0000079B
#define Excel_AppGenerateGetPivotData                 0x0000079C
#define Excel_AppAutoRecover                          0x0000079D
#define Excel_AppHwnd                                 0x0000079E
#define Excel_AppHinstance                            0x0000079F
#define Excel_AppErrorCheckingOptions                 0x000007A2
#define Excel_AppAutoFormatAsYouTypeReplaceHyperlinks 0x000007A3
#define Excel_AppSmartTagRecognizers                  0x000007A4
#define Excel_AppSpellingOptions                      0x000007A5
#define Excel_AppSpeech                               0x000007A6
#define Excel_AppMapPaperSize                         0x000007A7
#define Excel_AppShowStartupDialog                    0x000007A8
#define Excel_AppUseSystemSeparators                  0x000007A9
#define Excel_AppThisCell                             0x000007AA
#define Excel_AppRTD                                  0x000007AB
#define Excel_AppDisplayDocumentActionTaskPane        0x000008CB
#define Excel_AppArbitraryXMLSupportAvailable         0x000008CE
/* NICDBLD_END> Object Name: _Application */

/* NICDBLD_BEGIN> Object Name: _Worksheet */
#define Excel_Worksheet_CodeName                  0x80010000
#define Excel_WorksheetOutline                    0x00000066
#define Excel_WorksheetType                       0x0000006C
#define Excel_WorksheetName                       0x0000006E
#define Excel_WorksheetApplication                0x00000094
#define Excel_WorksheetCreator                    0x00000095
#define Excel_WorksheetParent                     0x00000096
#define Excel_WorksheetProtection                 0x000000B0
#define Excel_WorksheetCells                      0x000000EE
#define Excel_WorksheetColumns                    0x000000F1
#define Excel_WorksheetRows                       0x00000102
#define Excel_WorksheetProtectContents            0x00000124
#define Excel_WorksheetProtectDrawingObjects      0x00000125
#define Excel_WorksheetProtectScenarios           0x00000126
#define Excel_WorksheetTransitionExpEval          0x00000191
#define Excel_WorksheetTransitionFormEntry        0x00000192
#define Excel_WorksheetStandardHeight             0x00000197
#define Excel_WorksheetStandardWidth              0x00000198
#define Excel_WorksheetUsedRange                  0x0000019C
#define Excel_WorksheetNames                      0x000001BA
#define Excel_WorksheetIndex                      0x000001E6
#define Excel_WorksheetNext                       0x000001F6
#define Excel_WorksheetPrevious                   0x000001F7
#define Excel_WorksheetVisible                    0x0000022E
#define Excel_WorksheetComments                   0x0000023F
#define Excel_WorksheetOnCalculate                0x00000271
#define Excel_WorksheetOnEntry                    0x00000273
#define Excel_WorksheetOnDoubleClick              0x00000274
#define Excel_WorksheetOnData                     0x00000275
#define Excel_WorksheetDisplayAutomaticPageBreaks 0x00000283
#define Excel_Worksheet_DisplayRightToLeft        0x00000288
#define Excel_WorksheetConsolidationFunction      0x00000315
#define Excel_WorksheetConsolidationOptions       0x00000316
#define Excel_WorksheetConsolidationSources       0x00000317
#define Excel_WorksheetAutoFilterMode             0x00000318
#define Excel_WorksheetAutoFilter                 0x00000319
#define Excel_WorksheetFilterMode                 0x00000320
#define Excel_WorksheetPageSetup                  0x000003E6
#define Excel_WorksheetOnSheetActivate            0x00000407
#define Excel_WorksheetTab                        0x00000411
#define Excel_WorksheetCircularReference          0x0000042D
#define Excel_WorksheetOnSheetDeactivate          0x00000439
#define Excel_WorksheetEnableAutoFilter           0x00000484
#define Excel_WorksheetEnableOutlining            0x00000485
#define Excel_WorksheetEnablePivotTable           0x00000486
#define Excel_WorksheetProtectionMode             0x00000487
#define Excel_WorksheetCodeName                   0x0000055D
#define Excel_WorksheetShapes                     0x00000561
#define Excel_WorksheetHyperlinks                 0x00000571
#define Excel_WorksheetHPageBreaks                0x0000058A
#define Excel_WorksheetVPageBreaks                0x0000058B
#define Excel_WorksheetEnableCalculation          0x00000590
#define Excel_WorksheetEnableSelection            0x00000591
#define Excel_WorksheetScrollArea                 0x00000599
#define Excel_WorksheetQueryTables                0x0000059A
#define Excel_WorksheetDisplayPageBreaks          0x0000059B
#define Excel_WorksheetDisplayRightToLeft         0x000006EE
#define Excel_WorksheetScripts                    0x00000718
#define Excel_WorksheetSmartTags                  0x000007E0
#define Excel_WorksheetMailEnvelope               0x000007E5
#define Excel_WorksheetCustomProperties           0x000007EE
#define Excel_WorksheetListObjects                0x000008D3
/* NICDBLD_END> Object Name: _Worksheet */

/* NICDBLD_BEGIN> Object Name: _Global */
#define Excel_GlobalCharts                0x00000079
#define Excel_GlobalSelection             0x00000093
#define Excel_GlobalApplication           0x00000094
#define Excel_GlobalCreator               0x00000095
#define Excel_GlobalParent                0x00000096
#define Excel_GlobalActiveChart           0x000000B7
#define Excel_GlobalCells                 0x000000EE
#define Excel_GlobalColumns               0x000000F1
#define Excel_GlobalRows                  0x00000102
#define Excel_GlobalActiveCell            0x00000131
#define Excel_GlobalActivePrinter         0x00000132
#define Excel_GlobalActiveSheet           0x00000133
#define Excel_GlobalActiveWorkbook        0x00000134
#define Excel_GlobalDDEAppReturnCode      0x0000014C
#define Excel_GlobalWindows               0x000001AE
#define Excel_GlobalNames                 0x000001BA
#define Excel_GlobalSheets                0x000001E5
#define Excel_GlobalWorksheets            0x000001EE
#define Excel_GlobalAddIns                0x00000225
#define Excel_GlobalToolbars              0x00000228
#define Excel_GlobalWorkbooks             0x0000023C
#define Excel_GlobalExcel4MacroSheets     0x00000243
#define Excel_GlobalExcel4IntlMacroSheets 0x00000245
#define Excel_GlobalModules               0x00000246
#define Excel_GlobalMenuBars              0x0000024D
#define Excel_GlobalActiveMenuBar         0x000002F6
#define Excel_GlobalActiveWindow          0x000002F7
#define Excel_GlobalDialogSheets          0x000002FC
#define Excel_GlobalThisWorkbook          0x0000030A
#define Excel_GlobalActiveDialog          0x0000032F
#define Excel_GlobalAssistant             0x0000059E
#define Excel_GlobalCommandBars           0x0000059F
#define Excel_GlobalWorksheetFunction     0x000005A0
/* NICDBLD_END> Object Name: _Global */

/* NICDBLD_BEGIN> Object Name: _Workbook */
#define Excel_Workbook_CodeName                        0x80010000
#define Excel_WorkbookName                             0x0000006E
#define Excel_WorkbookCharts                           0x00000079
#define Excel_WorkbookApplication                      0x00000094
#define Excel_WorkbookCreator                          0x00000095
#define Excel_WorkbookParent                           0x00000096
#define Excel_WorkbookActiveChart                      0x000000B7
#define Excel_WorkbookTitle                            0x000000C7
#define Excel_WorkbookCreateBackup                     0x0000011F
#define Excel_WorkbookFileFormat                       0x00000120
#define Excel_WorkbookFullName                         0x00000121
#define Excel_WorkbookHasPassword                      0x00000122
#define Excel_WorkbookPath                             0x00000123
#define Excel_WorkbookProtectWindows                   0x00000127
#define Excel_WorkbookReadOnly                         0x00000128
#define Excel_Workbook_ReadOnlyRecommended             0x00000129
#define Excel_WorkbookSaved                            0x0000012A
#define Excel_WorkbookWriteReserved                    0x0000012B
#define Excel_WorkbookWriteReservedBy                  0x0000012C
#define Excel_WorkbookActiveSheet                      0x00000133
#define Excel_WorkbookDate1904                         0x00000193
#define Excel_WorkbookDisplayDrawingObjects            0x00000194
#define Excel_WorkbookPrecisionAsDisplayed             0x00000195
#define Excel_WorkbookSaveLinkValues                   0x00000196
#define Excel_WorkbookUpdateRemoteReferences           0x0000019B
#define Excel_WorkbookPassword                         0x000001AD
#define Excel_WorkbookWindows                          0x000001AE
#define Excel_WorkbookNames                            0x000001BA
#define Excel_WorkbookSheets                           0x000001E5
#define Excel_WorkbookStyles                           0x000001ED
#define Excel_WorkbookWorksheets                       0x000001EE
#define Excel_WorkbookAuthor                           0x0000023E
#define Excel_WorkbookComments                         0x0000023F
#define Excel_WorkbookKeywords                         0x00000241
#define Excel_WorkbookExcel4MacroSheets                0x00000243
#define Excel_WorkbookExcel4IntlMacroSheets            0x00000245
#define Excel_WorkbookModules                          0x00000246
#define Excel_WorkbookProtectStructure                 0x0000024C
#define Excel_WorkbookDialogSheets                     0x000002FC
#define Excel_WorkbookUpdateLinks                      0x00000360
#define Excel_WorkbookRoutingSlip                      0x000003B5
#define Excel_WorkbookHasRoutingSlip                   0x000003B6
#define Excel_WorkbookRouted                           0x000003B7
#define Excel_WorkbookSubject                          0x000003B9
#define Excel_WorkbookHasMailer                        0x000003D0
#define Excel_WorkbookMailer                           0x000003D3
#define Excel_WorkbookOnSheetActivate                  0x00000407
#define Excel_WorkbookOnSheetDeactivate                0x00000439
#define Excel_WorkbookWritePassword                    0x00000468
#define Excel_WorkbookMultiUserEditing                 0x00000491
#define Excel_WorkbookShowConflictHistory              0x00000493
#define Excel_WorkbookRevisionNumber                   0x00000494
#define Excel_WorkbookUserStatus                       0x00000495
#define Excel_WorkbookConflictResolution               0x00000497
#define Excel_WorkbookBuiltinDocumentProperties        0x00000498
#define Excel_WorkbookCustomDocumentProperties         0x00000499
#define Excel_WorkbookOnSave                           0x0000049A
#define Excel_WorkbookContainer                        0x000004A6
#define Excel_WorkbookUserControl                      0x000004BA
#define Excel_WorkbookCodeName                         0x0000055D
#define Excel_WorkbookCommandBars                      0x0000059F
#define Excel_WorkbookAcceptLabelsInFormulas           0x000005A1
#define Excel_WorkbookAutoUpdateFrequency              0x000005A2
#define Excel_WorkbookAutoUpdateSaveChanges            0x000005A3
#define Excel_WorkbookChangeHistoryDuration            0x000005A4
#define Excel_WorkbookIsAddin                          0x000005A5
#define Excel_WorkbookPersonalViewListSettings         0x000005A7
#define Excel_WorkbookPersonalViewPrintSettings        0x000005A8
#define Excel_WorkbookCustomViews                      0x000005B0
#define Excel_WorkbookTemplateRemoveExtData            0x000005B1
#define Excel_WorkbookHighlightChangesOnScreen         0x000005B5
#define Excel_WorkbookKeepChangeHistory                0x000005B6
#define Excel_WorkbookListChangesOnNewSheet            0x000005B7
#define Excel_WorkbookVBProject                        0x000005BD
#define Excel_WorkbookIsInplace                        0x000006E9
#define Excel_WorkbookCalculationVersion               0x0000070E
#define Excel_WorkbookPublishObjects                   0x0000071B
#define Excel_WorkbookWebOptions                       0x0000071C
#define Excel_WorkbookHTMLProject                      0x0000071F
#define Excel_WorkbookEnvelopeVisible                  0x00000720
#define Excel_WorkbookVBASigned                        0x00000724
#define Excel_WorkbookFullNameURLEncoded               0x00000787
#define Excel_WorkbookReadOnlyRecommended              0x000007D5
#define Excel_WorkbookShowPivotTableFieldList          0x000007FE
#define Excel_WorkbookEnableAutoRecover                0x00000801
#define Excel_WorkbookRemovePersonalInformation        0x00000802
#define Excel_WorkbookPasswordEncryptionProvider       0x0000080B
#define Excel_WorkbookPasswordEncryptionAlgorithm      0x0000080C
#define Excel_WorkbookPasswordEncryptionKeyLength      0x0000080D
#define Excel_WorkbookPasswordEncryptionFileProperties 0x0000080F
#define Excel_WorkbookSmartTagOptions                  0x00000810
#define Excel_WorkbookPermission                       0x000008D8
#define Excel_WorkbookSharedWorkspace                  0x000008D9
#define Excel_WorkbookSync                             0x000008DA
#define Excel_WorkbookXmlNamespaces                    0x000008DC
#define Excel_WorkbookXmlMaps                          0x000008DD
#define Excel_WorkbookSmartDocument                    0x000008E1
#define Excel_WorkbookDocumentLibraryVersions          0x000008E2
#define Excel_WorkbookInactiveListBorderVisible        0x000008E3
#define Excel_WorkbookDisplayInkComments               0x000008E4
/* NICDBLD_END> Object Name: _Workbook */

/* NICDBLD_BEGIN> Object Name: Sheets */
#define Excel_Sheets_NewEnum    0xFFFFFFFC
#define Excel_SheetsCount       0x00000076
#define Excel_SheetsApplication 0x00000094
#define Excel_SheetsCreator     0x00000095
#define Excel_SheetsParent      0x00000096
#define Excel_SheetsVisible     0x0000022E
#define Excel_SheetsHPageBreaks 0x0000058A
#define Excel_SheetsVPageBreaks 0x0000058B
/* NICDBLD_END> Object Name: Sheets */

/* NICDBLD_BEGIN> Object Name: Workbooks */
#define Excel_Workbooks_NewEnum    0xFFFFFFFC
#define Excel_WorkbooksCount       0x00000076
#define Excel_WorkbooksApplication 0x00000094
#define Excel_WorkbooksCreator     0x00000095
#define Excel_WorkbooksParent      0x00000096
/* NICDBLD_END> Object Name: Workbooks */

/* NICDBLD_BEGIN> Object Name: Font */
#define Excel_FontBold          0x00000060
#define Excel_FontColorIndex    0x00000061
#define Excel_FontColor         0x00000063
#define Excel_FontItalic        0x00000065
#define Excel_FontShadow        0x00000067
#define Excel_FontSize          0x00000068
#define Excel_FontStrikethrough 0x00000069
#define Excel_FontUnderline     0x0000006A
#define Excel_FontName          0x0000006E
#define Excel_FontApplication   0x00000094
#define Excel_FontCreator       0x00000095
#define Excel_FontParent        0x00000096
#define Excel_FontFontStyle     0x000000B1
#define Excel_FontSuperscript   0x000000B2
#define Excel_FontSubscript     0x000000B3
#define Excel_FontBackground    0x000000B4
#define Excel_FontOutlineFont   0x000000DD
/* NICDBLD_END> Object Name: Font */

/* NICDBLD_BEGIN> Object Name: Range */
#define Excel_Range_NewEnum            0xFFFFFFFC
#define Excel_RangeName                0x0000006E
#define Excel_RangeCount               0x00000076
#define Excel_RangeWidth               0x0000007A
#define Excel_RangeHeight              0x0000007B
#define Excel_RangeTop                 0x0000007E
#define Excel_RangeLeft                0x0000007F
#define Excel_RangeInterior            0x00000081
#define Excel_RangeOrientation         0x00000086
#define Excel_RangeHorizontalAlignment 0x00000088
#define Excel_RangeVerticalAlignment   0x00000089
#define Excel_RangeText                0x0000008A
#define Excel_RangeFont                0x00000092
#define Excel_RangeApplication         0x00000094
#define Excel_RangeCreator             0x00000095
#define Excel_RangeParent              0x00000096
#define Excel_RangeNumberFormat        0x000000C1
#define Excel_RangeIndentLevel         0x000000C9
#define Excel_RangeMergeCells          0x000000D0
#define Excel_RangeShrinkToFit         0x000000D1
#define Excel_RangeCells               0x000000EE
#define Excel_RangeColumn              0x000000F0
#define Excel_RangeColumns             0x000000F1
#define Excel_RangeColumnWidth         0x000000F2
#define Excel_RangeCurrentRegion       0x000000F3
#define Excel_RangeEntireColumn        0x000000F6
#define Excel_RangeEntireRow           0x000000F7
#define Excel_RangePageBreak           0x000000FF
#define Excel_RangeRow                 0x00000101
#define Excel_RangeRows                0x00000102
#define Excel_RangeStyle               0x00000104
#define Excel_RangeFormula             0x00000105
#define Excel_RangeFormulaHidden       0x00000106
#define Excel_RangeFormulaLocal        0x00000107
#define Excel_RangeFormulaR1C1         0x00000108
#define Excel_RangeFormulaR1C1Local    0x00000109
#define Excel_RangeHasArray            0x0000010A
#define Excel_RangeHasFormula          0x0000010B
#define Excel_RangeHidden              0x0000010C
#define Excel_RangeLocked              0x0000010D
#define Excel_RangeOutlineLevel        0x0000010F
#define Excel_RangeRowHeight           0x00000110
#define Excel_RangeSummary             0x00000111
#define Excel_RangeUseStandardHeight   0x00000112
#define Excel_RangeUseStandardWidth    0x00000113
#define Excel_RangeWrapText            0x00000114
#define Excel_RangeWorksheet           0x0000015C
#define Excel_RangeBorders             0x000001B3
#define Excel_RangeCurrentArray        0x000001F5
#define Excel_RangeNext                0x000001F6
#define Excel_RangePrevious            0x000001F7
#define Excel_RangePrefixCharacter     0x000001F8
#define Excel_RangeDependents          0x0000021F
#define Excel_RangePrecedents          0x00000220
#define Excel_RangeDirectDependents    0x00000221
#define Excel_RangeDirectPrecedents    0x00000222
#define Excel_RangeAreas               0x00000238
#define Excel_RangeShowDetail          0x00000249
#define Excel_RangeFormulaArray        0x0000024A
#define Excel_RangeLocationInTable     0x000002B3
#define Excel_RangePivotTable          0x000002CC
#define Excel_RangePivotField          0x000002DB
#define Excel_RangePivotItem           0x000002E4
#define Excel_RangeComment             0x0000038E
#define Excel_RangeSoundNote           0x00000394
#define Excel_RangeReadingOrder        0x000003CF
#define Excel_RangeAddIndent           0x00000427
#define Excel_RangeNumberFormatLocal   0x00000449
#define Excel_RangeListHeaderRows      0x000004A3
#define Excel_RangeFormulaLabel        0x00000564
#define Excel_RangeMergeArea           0x00000569
#define Excel_RangeQueryTable          0x0000056A
#define Excel_RangeValidation          0x0000056B
#define Excel_RangeValue2              0x0000056C
#define Excel_RangePhonetic            0x0000056F
#define Excel_RangeFormatConditions    0x00000570
#define Excel_RangeHyperlinks          0x00000571
#define Excel_RangePhonetics           0x00000713
#define Excel_RangeID                  0x00000715
#define Excel_RangePivotCell           0x000007DD
#define Excel_RangeErrors              0x000007DF
#define Excel_RangeSmartTags           0x000007E0
#define Excel_RangeAllowEdit           0x000007E4
#define Excel_RangeListObject          0x000008D1
#define Excel_RangeXPath               0x000008D2
/* NICDBLD_END> Object Name: Range */
/* NICDBLD_END> ActiveX Automation Properties */

/* NICDBLD_BEGIN> Type Library Specific Types */
enum ExcelEnum_XlCreator
{
   ExcelConst_xlCreatorCode = 1480803660,
   _Excel_XlCreatorForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCellInsertionMode
{
   ExcelConst_xlOverwriteCells = 0,
   ExcelConst_xlInsertDeleteCells = 1,
   ExcelConst_xlInsertEntireRows = 2,
   _Excel_XlCellInsertionModeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTextParsingType
{
   ExcelConst_xlDelimited = 1,
   ExcelConst_xlFixedWidth = 2,
   _Excel_XlTextParsingTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTextQualifier
{
   ExcelConst_xlTextQualifierDoubleQuote = 1,
   ExcelConst_xlTextQualifierNone = -4142,
   ExcelConst_xlTextQualifierSingleQuote = 2,
   _Excel_XlTextQualifierForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCmdType
{
   ExcelConst_xlCmdCube = 1,
   ExcelConst_xlCmdSql = 2,
   ExcelConst_xlCmdTable = 3,
   ExcelConst_xlCmdDefault = 4,
   ExcelConst_xlCmdList = 5,
   _Excel_XlCmdTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlQueryType
{
   ExcelConst_xlODBCQuery = 1,
   ExcelConst_xlDAORecordset = 2,
   ExcelConst_xlWebQuery = 4,
   ExcelConst_xlOLEDBQuery = 5,
   ExcelConst_xlTextImport = 6,
   ExcelConst_xlADORecordset = 7,
   _Excel_XlQueryTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlWebSelectionType
{
   ExcelConst_xlEntirePage = 1,
   ExcelConst_xlAllTables = 2,
   ExcelConst_xlSpecifiedTables = 3,
   _Excel_XlWebSelectionTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlWebFormatting
{
   ExcelConst_xlWebFormattingAll = 1,
   ExcelConst_xlWebFormattingRTF = 2,
   ExcelConst_xlWebFormattingNone = 3,
   _Excel_XlWebFormattingForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlRobustConnect
{
   ExcelConst_xlAsRequired = 0,
   ExcelConst_xlAlways = 1,
   ExcelConst_xlNever = 2,
   _Excel_XlRobustConnectForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTextVisualLayoutType
{
   ExcelConst_xlTextVisualLTR = 1,
   ExcelConst_xlTextVisualRTL = 2,
   _Excel_XlTextVisualLayoutTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlMSApplication
{
   ExcelConst_xlMicrosoftAccess = 4,
   ExcelConst_xlMicrosoftFoxPro = 5,
   ExcelConst_xlMicrosoftMail = 3,
   ExcelConst_xlMicrosoftPowerPoint = 2,
   ExcelConst_xlMicrosoftProject = 6,
   ExcelConst_xlMicrosoftSchedulePlus = 7,
   ExcelConst_xlMicrosoftWord = 1,
   _Excel_XlMSApplicationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCalculation
{
   ExcelConst_xlCalculationAutomatic = -4105,
   ExcelConst_xlCalculationManual = -4135,
   ExcelConst_xlCalculationSemiautomatic = 2,
   _Excel_XlCalculationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCommandUnderlines
{
   ExcelConst_xlCommandUnderlinesAutomatic = -4105,
   ExcelConst_xlCommandUnderlinesOff = -4146,
   ExcelConst_xlCommandUnderlinesOn = 1,
   _Excel_XlCommandUnderlinesForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlReferenceStyle
{
   ExcelConst_xlA1 = 1,
   ExcelConst_xlR1C1 = -4150,
   _Excel_XlReferenceStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlMousePointer
{
   ExcelConst_xlIBeam = 3,
   ExcelConst_xlDefault = -4143,
   ExcelConst_xlNorthwestArrow = 1,
   ExcelConst_xlWait = 2,
   _Excel_XlMousePointerForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCutCopyMode
{
   ExcelConst_xlCopy = 1,
   ExcelConst_xlCut = 2,
   _Excel_XlCutCopyModeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCommentDisplayMode
{
   ExcelConst_xlNoIndicator = 0,
   ExcelConst_xlCommentIndicatorOnly = -1,
   ExcelConst_xlCommentAndIndicator = 1,
   _Excel_XlCommentDisplayModeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlEnableCancelKey
{
   ExcelConst_xlDisabled = 0,
   ExcelConst_xlErrorHandler = 2,
   ExcelConst_xlInterrupt = 1,
   _Excel_XlEnableCancelKeyForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlMailSystem
{
   ExcelConst_xlMAPI = 1,
   ExcelConst_xlNoMailSystem = 0,
   ExcelConst_xlPowerTalk = 2,
   _Excel_XlMailSystemForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDirection
{
   ExcelConst_xlDown = -4121,
   ExcelConst_xlToLeft = -4159,
   ExcelConst_xlToRight = -4161,
   ExcelConst_xlUp = -4162,
   _Excel_XlDirectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFileFormat
{
   ExcelConst_xlAddIn = 18,
   ExcelConst_xlCSV = 6,
   ExcelConst_xlCSVMac = 22,
   ExcelConst_xlCSVMSDOS = 24,
   ExcelConst_xlCSVWindows = 23,
   ExcelConst_xlDBF2 = 7,
   ExcelConst_xlDBF3 = 8,
   ExcelConst_xlDBF4 = 11,
   ExcelConst_xlDIF = 9,
   ExcelConst_xlExcel2 = 16,
   ExcelConst_xlExcel2FarEast = 27,
   ExcelConst_xlExcel3 = 29,
   ExcelConst_xlExcel4 = 33,
   ExcelConst_xlExcel5 = 39,
   ExcelConst_xlExcel7 = 39,
   ExcelConst_xlExcel9795 = 43,
   ExcelConst_xlExcel4Workbook = 35,
   ExcelConst_xlIntlAddIn = 26,
   ExcelConst_xlIntlMacro = 25,
   ExcelConst_xlWorkbookNormal = -4143,
   ExcelConst_xlSYLK = 2,
   ExcelConst_xlTemplate = 17,
   ExcelConst_xlCurrentPlatformText = -4158,
   ExcelConst_xlTextMac = 19,
   ExcelConst_xlTextMSDOS = 21,
   ExcelConst_xlTextPrinter = 36,
   ExcelConst_xlTextWindows = 20,
   ExcelConst_xlWJ2WD1 = 14,
   ExcelConst_xlWK1 = 5,
   ExcelConst_xlWK1ALL = 31,
   ExcelConst_xlWK1FMT = 30,
   ExcelConst_xlWK3 = 15,
   ExcelConst_xlWK4 = 38,
   ExcelConst_xlWK3FM3 = 32,
   ExcelConst_xlWKS = 4,
   ExcelConst_xlWorks2FarEast = 28,
   ExcelConst_xlWQ1 = 34,
   ExcelConst_xlWJ3 = 40,
   ExcelConst_xlWJ3FJ3 = 41,
   ExcelConst_xlUnicodeText = 42,
   ExcelConst_xlHtml = 44,
   ExcelConst_xlWebArchive = 45,
   ExcelConst_xlXMLSpreadsheet = 46,
   _Excel_XlFileFormatForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlWindowState
{
   ExcelConst_xlMaximized = -4137,
   ExcelConst_xlMinimized = -4140,
   ExcelConst_xlNormal = -4143,
   _Excel_XlWindowStateForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoFeatureInstall
{
   ExcelConst_msoFeatureInstallNone = 0,
   ExcelConst_msoFeatureInstallOnDemand = 1,
   ExcelConst_msoFeatureInstallOnDemandWithUI = 2,
   _Excel_MsoFeatureInstallForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCalculationState
{
   ExcelConst_xlDone = 0,
   ExcelConst_xlCalculating = 1,
   ExcelConst_xlPending = 2,
   _Excel_XlCalculationStateForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCalculationInterruptKey
{
   ExcelConst_xlNoKey = 0,
   ExcelConst_xlEscKey = 1,
   ExcelConst_xlAnyKey = 2,
   _Excel_XlCalculationInterruptKeyForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoAutomationSecurity
{
   ExcelConst_msoAutomationSecurityLow = 1,
   ExcelConst_msoAutomationSecurityByUI = 2,
   ExcelConst_msoAutomationSecurityForceDisable = 3,
   _Excel_MsoAutomationSecurityForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoFileDialogType
{
   ExcelConst_msoFileDialogOpen = 1,
   ExcelConst_msoFileDialogSaveAs = 2,
   ExcelConst_msoFileDialogFilePicker = 3,
   ExcelConst_msoFileDialogFolderPicker = 4,
   _Excel_MsoFileDialogTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoSyncEventType
{
   ExcelConst_msoSyncEventDownloadInitiated = 0,
   ExcelConst_msoSyncEventDownloadSucceeded = 1,
   ExcelConst_msoSyncEventDownloadFailed = 2,
   ExcelConst_msoSyncEventUploadInitiated = 3,
   ExcelConst_msoSyncEventUploadSucceeded = 4,
   ExcelConst_msoSyncEventUploadFailed = 5,
   ExcelConst_msoSyncEventDownloadNoChange = 6,
   ExcelConst_msoSyncEventOffline = 7,
   _Excel_MsoSyncEventTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlXmlImportResult
{
   ExcelConst_xlXmlImportSuccess = 0,
   ExcelConst_xlXmlImportElementsTruncated = 1,
   ExcelConst_xlXmlImportValidationFailed = 2,
   _Excel_XlXmlImportResultForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlXmlExportResult
{
   ExcelConst_xlXmlExportSuccess = 0,
   ExcelConst_xlXmlExportValidationFailed = 1,
   _Excel_XlXmlExportResultForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSheetVisibility
{
   ExcelConst_xlSheetVisible = -1,
   ExcelConst_xlSheetHidden = 0,
   ExcelConst_xlSheetVeryHidden = 2,
   _Excel_XlSheetVisibilityForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDataLabelsType
{
   ExcelConst_xlDataLabelsShowNone = -4142,
   ExcelConst_xlDataLabelsShowValue = 2,
   ExcelConst_xlDataLabelsShowPercent = 3,
   ExcelConst_xlDataLabelsShowLabel = 4,
   ExcelConst_xlDataLabelsShowLabelAndPercent = 5,
   ExcelConst_xlDataLabelsShowBubbleSizes = 6,
   _Excel_XlDataLabelsTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlAxisGroup
{
   ExcelConst_xlPrimary = 1,
   ExcelConst_xlSecondary = 2,
   _Excel_XlAxisGroupForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPictureAppearance
{
   ExcelConst_xlPrinter = 2,
   ExcelConst_xlScreen = 1,
   _Excel_XlPictureAppearanceForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCopyPictureFormat
{
   ExcelConst_xlBitmap = 2,
   ExcelConst_xlPicture = -4147,
   _Excel_XlCopyPictureFormatForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDisplayBlanksAs
{
   ExcelConst_xlInterpolated = 3,
   ExcelConst_xlNotPlotted = 1,
   ExcelConst_xlZero = 2,
   _Excel_XlDisplayBlanksAsForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlChartLocation
{
   ExcelConst_xlLocationAsNewSheet = 1,
   ExcelConst_xlLocationAsObject = 2,
   ExcelConst_xlLocationAutomatic = 3,
   _Excel_XlChartLocationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlChartType
{
   ExcelConst_xlColumnClustered = 51,
   ExcelConst_xlColumnStacked = 52,
   ExcelConst_xlColumnStacked100 = 53,
   ExcelConst_xl3DColumnClustered = 54,
   ExcelConst_xl3DColumnStacked = 55,
   ExcelConst_xl3DColumnStacked100 = 56,
   ExcelConst_xlBarClustered = 57,
   ExcelConst_xlBarStacked = 58,
   ExcelConst_xlBarStacked100 = 59,
   ExcelConst_xl3DBarClustered = 60,
   ExcelConst_xl3DBarStacked = 61,
   ExcelConst_xl3DBarStacked100 = 62,
   ExcelConst_xlLineStacked = 63,
   ExcelConst_xlLineStacked100 = 64,
   ExcelConst_xlLineMarkers = 65,
   ExcelConst_xlLineMarkersStacked = 66,
   ExcelConst_xlLineMarkersStacked100 = 67,
   ExcelConst_xlPieOfPie = 68,
   ExcelConst_xlPieExploded = 69,
   ExcelConst_xl3DPieExploded = 70,
   ExcelConst_xlBarOfPie = 71,
   ExcelConst_xlXYScatterSmooth = 72,
   ExcelConst_xlXYScatterSmoothNoMarkers = 73,
   ExcelConst_xlXYScatterLines = 74,
   ExcelConst_xlXYScatterLinesNoMarkers = 75,
   ExcelConst_xlAreaStacked = 76,
   ExcelConst_xlAreaStacked100 = 77,
   ExcelConst_xl3DAreaStacked = 78,
   ExcelConst_xl3DAreaStacked100 = 79,
   ExcelConst_xlDoughnutExploded = 80,
   ExcelConst_xlRadarMarkers = 81,
   ExcelConst_xlRadarFilled = 82,
   ExcelConst_xlSurface = 83,
   ExcelConst_xlSurfaceWireframe = 84,
   ExcelConst_xlSurfaceTopView = 85,
   ExcelConst_xlSurfaceTopViewWireframe = 86,
   ExcelConst_xlBubble = 15,
   ExcelConst_xlBubble3DEffect = 87,
   ExcelConst_xlStockHLC = 88,
   ExcelConst_xlStockOHLC = 89,
   ExcelConst_xlStockVHLC = 90,
   ExcelConst_xlStockVOHLC = 91,
   ExcelConst_xlCylinderColClustered = 92,
   ExcelConst_xlCylinderColStacked = 93,
   ExcelConst_xlCylinderColStacked100 = 94,
   ExcelConst_xlCylinderBarClustered = 95,
   ExcelConst_xlCylinderBarStacked = 96,
   ExcelConst_xlCylinderBarStacked100 = 97,
   ExcelConst_xlCylinderCol = 98,
   ExcelConst_xlConeColClustered = 99,
   ExcelConst_xlConeColStacked = 100,
   ExcelConst_xlConeColStacked100 = 101,
   ExcelConst_xlConeBarClustered = 102,
   ExcelConst_xlConeBarStacked = 103,
   ExcelConst_xlConeBarStacked100 = 104,
   ExcelConst_xlConeCol = 105,
   ExcelConst_xlPyramidColClustered = 106,
   ExcelConst_xlPyramidColStacked = 107,
   ExcelConst_xlPyramidColStacked100 = 108,
   ExcelConst_xlPyramidBarClustered = 109,
   ExcelConst_xlPyramidBarStacked = 110,
   ExcelConst_xlPyramidBarStacked100 = 111,
   ExcelConst_xlPyramidCol = 112,
   ExcelConst_xl3DColumn = -4100,
   ExcelConst_xlLine = 4,
   ExcelConst_xl3DLine = -4101,
   ExcelConst_xl3DPie = -4102,
   ExcelConst_xlPie = 5,
   ExcelConst_xlXYScatter = -4169,
   ExcelConst_xl3DArea = -4098,
   ExcelConst_xlArea = 1,
   ExcelConst_xlDoughnut = -4120,
   ExcelConst_xlRadar = -4151,
   _Excel_XlChartTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlBarShape
{
   ExcelConst_xlBox = 0,
   ExcelConst_xlPyramidToPoint = 1,
   ExcelConst_xlPyramidToMax = 2,
   ExcelConst_xlCylinder = 3,
   ExcelConst_xlConeToPoint = 4,
   ExcelConst_xlConeToMax = 5,
   _Excel_XlBarShapeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlRowCol
{
   ExcelConst_xlColumns = 2,
   ExcelConst_xlRows = 1,
   _Excel_XlRowColForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlConsolidationFunction
{
   ExcelConst_xlAverage = -4106,
   ExcelConst_xlCount = -4112,
   ExcelConst_xlCountNums = -4113,
   ExcelConst_xlMax = -4136,
   ExcelConst_xlMin = -4139,
   ExcelConst_xlProduct = -4149,
   ExcelConst_xlStDev = -4155,
   ExcelConst_xlStDevP = -4156,
   ExcelConst_xlSum = -4157,
   ExcelConst_xlVar = -4164,
   ExcelConst_xlVarP = -4165,
   ExcelConst_xlUnknown = 1000,
   _Excel_XlConsolidationFunctionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlEnableSelection
{
   ExcelConst_xlNoRestrictions = 0,
   ExcelConst_xlUnlockedCells = 1,
   ExcelConst_xlNoSelection = -4142,
   _Excel_XlEnableSelectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSheetType
{
   ExcelConst_xlChart = -4109,
   ExcelConst_xlDialogSheet = -4116,
   ExcelConst_xlExcel4IntlMacroSheet = 4,
   ExcelConst_xlExcel4MacroSheet = 3,
   ExcelConst_xlWorksheet = -4167,
   _Excel_XlSheetTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFileAccess
{
   ExcelConst_xlReadOnly = 3,
   ExcelConst_xlReadWrite = 2,
   _Excel_XlFileAccessForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLinkType
{
   ExcelConst_xlLinkTypeExcelLinks = 1,
   ExcelConst_xlLinkTypeOLELinks = 2,
   _Excel_XlLinkTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSaveConflictResolution
{
   ExcelConst_xlLocalSessionChanges = 2,
   ExcelConst_xlOtherSessionChanges = 3,
   ExcelConst_xlUserResolution = 1,
   _Excel_XlSaveConflictResolutionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDisplayDrawingObjects
{
   ExcelConst_xlDisplayShapes = -4104,
   ExcelConst_xlHide = 3,
   ExcelConst_xlPlaceholders = 2,
   _Excel_XlDisplayDrawingObjectsForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLinkInfo
{
   ExcelConst_xlEditionDate = 2,
   ExcelConst_xlUpdateState = 1,
   ExcelConst_xlLinkInfoStatus = 3,
   _Excel_XlLinkInfoForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlRunAutoMacro
{
   ExcelConst_xlAutoActivate = 3,
   ExcelConst_xlAutoClose = 2,
   ExcelConst_xlAutoDeactivate = 4,
   ExcelConst_xlAutoOpen = 1,
   _Excel_XlRunAutoMacroForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSaveAsAccessMode
{
   ExcelConst_xlExclusive = 3,
   ExcelConst_xlNoChange = 1,
   ExcelConst_xlShared = 2,
   _Excel_XlSaveAsAccessModeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPriority
{
   ExcelConst_xlPriorityHigh = -4127,
   ExcelConst_xlPriorityLow = -4134,
   ExcelConst_xlPriorityNormal = -4143,
   _Excel_XlPriorityForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoEncoding
{
   ExcelConst_msoEncodingThai = 874,
   ExcelConst_msoEncodingJapaneseShiftJIS = 932,
   ExcelConst_msoEncodingSimplifiedChineseGBK = 936,
   ExcelConst_msoEncodingKorean = 949,
   ExcelConst_msoEncodingTraditionalChineseBig5 = 950,
   ExcelConst_msoEncodingUnicodeLittleEndian = 1200,
   ExcelConst_msoEncodingUnicodeBigEndian = 1201,
   ExcelConst_msoEncodingCentralEuropean = 1250,
   ExcelConst_msoEncodingCyrillic = 1251,
   ExcelConst_msoEncodingWestern = 1252,
   ExcelConst_msoEncodingGreek = 1253,
   ExcelConst_msoEncodingTurkish = 1254,
   ExcelConst_msoEncodingHebrew = 1255,
   ExcelConst_msoEncodingArabic = 1256,
   ExcelConst_msoEncodingBaltic = 1257,
   ExcelConst_msoEncodingVietnamese = 1258,
   ExcelConst_msoEncodingAutoDetect = 50001,
   ExcelConst_msoEncodingJapaneseAutoDetect = 50932,
   ExcelConst_msoEncodingSimplifiedChineseAutoDetect = 50936,
   ExcelConst_msoEncodingKoreanAutoDetect = 50949,
   ExcelConst_msoEncodingTraditionalChineseAutoDetect = 50950,
   ExcelConst_msoEncodingCyrillicAutoDetect = 51251,
   ExcelConst_msoEncodingGreekAutoDetect = 51253,
   ExcelConst_msoEncodingArabicAutoDetect = 51256,
   ExcelConst_msoEncodingISO88591Latin1 = 28591,
   ExcelConst_msoEncodingISO88592CentralEurope = 28592,
   ExcelConst_msoEncodingISO88593Latin3 = 28593,
   ExcelConst_msoEncodingISO88594Baltic = 28594,
   ExcelConst_msoEncodingISO88595Cyrillic = 28595,
   ExcelConst_msoEncodingISO88596Arabic = 28596,
   ExcelConst_msoEncodingISO88597Greek = 28597,
   ExcelConst_msoEncodingISO88598Hebrew = 28598,
   ExcelConst_msoEncodingISO88599Turkish = 28599,
   ExcelConst_msoEncodingISO885915Latin9 = 28605,
   ExcelConst_msoEncodingISO88598HebrewLogical = 38598,
   ExcelConst_msoEncodingISO2022JPNoHalfwidthKatakana = 50220,
   ExcelConst_msoEncodingISO2022JPJISX02021984 = 50221,
   ExcelConst_msoEncodingISO2022JPJISX02011989 = 50222,
   ExcelConst_msoEncodingISO2022KR = 50225,
   ExcelConst_msoEncodingISO2022CNTraditionalChinese = 50227,
   ExcelConst_msoEncodingISO2022CNSimplifiedChinese = 50229,
   ExcelConst_msoEncodingMacRoman = 10000,
   ExcelConst_msoEncodingMacJapanese = 10001,
   ExcelConst_msoEncodingMacTraditionalChineseBig5 = 10002,
   ExcelConst_msoEncodingMacKorean = 10003,
   ExcelConst_msoEncodingMacArabic = 10004,
   ExcelConst_msoEncodingMacHebrew = 10005,
   ExcelConst_msoEncodingMacGreek1 = 10006,
   ExcelConst_msoEncodingMacCyrillic = 10007,
   ExcelConst_msoEncodingMacSimplifiedChineseGB2312 = 10008,
   ExcelConst_msoEncodingMacRomania = 10010,
   ExcelConst_msoEncodingMacUkraine = 10017,
   ExcelConst_msoEncodingMacLatin2 = 10029,
   ExcelConst_msoEncodingMacIcelandic = 10079,
   ExcelConst_msoEncodingMacTurkish = 10081,
   ExcelConst_msoEncodingMacCroatia = 10082,
   ExcelConst_msoEncodingEBCDICUSCanada = 37,
   ExcelConst_msoEncodingEBCDICInternational = 500,
   ExcelConst_msoEncodingEBCDICMultilingualROECELatin2 = 870,
   ExcelConst_msoEncodingEBCDICGreekModern = 875,
   ExcelConst_msoEncodingEBCDICTurkishLatin5 = 1026,
   ExcelConst_msoEncodingEBCDICGermany = 20273,
   ExcelConst_msoEncodingEBCDICDenmarkNorway = 20277,
   ExcelConst_msoEncodingEBCDICFinlandSweden = 20278,
   ExcelConst_msoEncodingEBCDICItaly = 20280,
   ExcelConst_msoEncodingEBCDICLatinAmericaSpain = 20284,
   ExcelConst_msoEncodingEBCDICUnitedKingdom = 20285,
   ExcelConst_msoEncodingEBCDICJapaneseKatakanaExtended = 20290,
   ExcelConst_msoEncodingEBCDICFrance = 20297,
   ExcelConst_msoEncodingEBCDICArabic = 20420,
   ExcelConst_msoEncodingEBCDICGreek = 20423,
   ExcelConst_msoEncodingEBCDICHebrew = 20424,
   ExcelConst_msoEncodingEBCDICKoreanExtended = 20833,
   ExcelConst_msoEncodingEBCDICThai = 20838,
   ExcelConst_msoEncodingEBCDICIcelandic = 20871,
   ExcelConst_msoEncodingEBCDICTurkish = 20905,
   ExcelConst_msoEncodingEBCDICRussian = 20880,
   ExcelConst_msoEncodingEBCDICSerbianBulgarian = 21025,
   ExcelConst_msoEncodingEBCDICJapaneseKatakanaExtendedAndJapanese = 50930,
   ExcelConst_msoEncodingEBCDICUSCanadaAndJapanese = 50931,
   ExcelConst_msoEncodingEBCDICKoreanExtendedAndKorean = 50933,
   ExcelConst_msoEncodingEBCDICSimplifiedChineseExtendedAndSimplifiedChinese = 50935,
   ExcelConst_msoEncodingEBCDICUSCanadaAndTraditionalChinese = 50937,
   ExcelConst_msoEncodingEBCDICJapaneseLatinExtendedAndJapanese = 50939,
   ExcelConst_msoEncodingOEMUnitedStates = 437,
   ExcelConst_msoEncodingOEMGreek437G = 737,
   ExcelConst_msoEncodingOEMBaltic = 775,
   ExcelConst_msoEncodingOEMMultilingualLatinI = 850,
   ExcelConst_msoEncodingOEMMultilingualLatinII = 852,
   ExcelConst_msoEncodingOEMCyrillic = 855,
   ExcelConst_msoEncodingOEMTurkish = 857,
   ExcelConst_msoEncodingOEMPortuguese = 860,
   ExcelConst_msoEncodingOEMIcelandic = 861,
   ExcelConst_msoEncodingOEMHebrew = 862,
   ExcelConst_msoEncodingOEMCanadianFrench = 863,
   ExcelConst_msoEncodingOEMArabic = 864,
   ExcelConst_msoEncodingOEMNordic = 865,
   ExcelConst_msoEncodingOEMCyrillicII = 866,
   ExcelConst_msoEncodingOEMModernGreek = 869,
   ExcelConst_msoEncodingEUCJapanese = 51932,
   ExcelConst_msoEncodingEUCChineseSimplifiedChinese = 51936,
   ExcelConst_msoEncodingEUCKorean = 51949,
   ExcelConst_msoEncodingEUCTaiwaneseTraditionalChinese = 51950,
   ExcelConst_msoEncodingISCIIDevanagari = 57002,
   ExcelConst_msoEncodingISCIIBengali = 57003,
   ExcelConst_msoEncodingISCIITamil = 57004,
   ExcelConst_msoEncodingISCIITelugu = 57005,
   ExcelConst_msoEncodingISCIIAssamese = 57006,
   ExcelConst_msoEncodingISCIIOriya = 57007,
   ExcelConst_msoEncodingISCIIKannada = 57008,
   ExcelConst_msoEncodingISCIIMalayalam = 57009,
   ExcelConst_msoEncodingISCIIGujarati = 57010,
   ExcelConst_msoEncodingISCIIPunjabi = 57011,
   ExcelConst_msoEncodingArabicASMO = 708,
   ExcelConst_msoEncodingArabicTransparentASMO = 720,
   ExcelConst_msoEncodingKoreanJohab = 1361,
   ExcelConst_msoEncodingTaiwanCNS = 20000,
   ExcelConst_msoEncodingTaiwanTCA = 20001,
   ExcelConst_msoEncodingTaiwanEten = 20002,
   ExcelConst_msoEncodingTaiwanIBM5550 = 20003,
   ExcelConst_msoEncodingTaiwanTeleText = 20004,
   ExcelConst_msoEncodingTaiwanWang = 20005,
   ExcelConst_msoEncodingIA5IRV = 20105,
   ExcelConst_msoEncodingIA5German = 20106,
   ExcelConst_msoEncodingIA5Swedish = 20107,
   ExcelConst_msoEncodingIA5Norwegian = 20108,
   ExcelConst_msoEncodingUSASCII = 20127,
   ExcelConst_msoEncodingT61 = 20261,
   ExcelConst_msoEncodingISO6937NonSpacingAccent = 20269,
   ExcelConst_msoEncodingKOI8R = 20866,
   ExcelConst_msoEncodingExtAlphaLowercase = 21027,
   ExcelConst_msoEncodingKOI8U = 21866,
   ExcelConst_msoEncodingEuropa3 = 29001,
   ExcelConst_msoEncodingHZGBSimplifiedChinese = 52936,
   ExcelConst_msoEncodingSimplifiedChineseGB18030 = 54936,
   ExcelConst_msoEncodingUTF7 = 65000,
   ExcelConst_msoEncodingUTF8 = 65001,
   _Excel_MsoEncodingForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlUpdateLinks
{
   ExcelConst_xlUpdateLinksUserSetting = 1,
   ExcelConst_xlUpdateLinksNever = 2,
   ExcelConst_xlUpdateLinksAlways = 3,
   _Excel_XlUpdateLinksForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlOLEVerb
{
   ExcelConst_xlVerbOpen = 2,
   ExcelConst_xlVerbPrimary = 1,
   _Excel_XlOLEVerbForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoCalloutDropType
{
   ExcelConst_msoCalloutDropMixed = -2,
   ExcelConst_msoCalloutDropCustom = 1,
   ExcelConst_msoCalloutDropTop = 2,
   ExcelConst_msoCalloutDropCenter = 3,
   ExcelConst_msoCalloutDropBottom = 4,
   _Excel_MsoCalloutDropTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoTriState
{
   ExcelConst_msoTrue = -1,
   ExcelConst_msoFalse = 0,
   ExcelConst_msoCTrue = 1,
   ExcelConst_msoTriStateToggle = -3,
   ExcelConst_msoTriStateMixed = -2,
   _Excel_MsoTriStateForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoCalloutAngleType
{
   ExcelConst_msoCalloutAngleMixed = -2,
   ExcelConst_msoCalloutAngleAutomatic = 1,
   ExcelConst_msoCalloutAngle30 = 2,
   ExcelConst_msoCalloutAngle45 = 3,
   ExcelConst_msoCalloutAngle60 = 4,
   ExcelConst_msoCalloutAngle90 = 5,
   _Excel_MsoCalloutAngleTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoCalloutType
{
   ExcelConst_msoCalloutMixed = -2,
   ExcelConst_msoCalloutOne = 1,
   ExcelConst_msoCalloutTwo = 2,
   ExcelConst_msoCalloutThree = 3,
   ExcelConst_msoCalloutFour = 4,
   _Excel_MsoCalloutTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoColorType
{
   ExcelConst_msoColorTypeMixed = -2,
   ExcelConst_msoColorTypeRGB = 1,
   ExcelConst_msoColorTypeScheme = 2,
   ExcelConst_msoColorTypeCMYK = 3,
   ExcelConst_msoColorTypeCMS = 4,
   ExcelConst_msoColorTypeInk = 5,
   _Excel_MsoColorTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoArrowheadLength
{
   ExcelConst_msoArrowheadLengthMixed = -2,
   ExcelConst_msoArrowheadShort = 1,
   ExcelConst_msoArrowheadLengthMedium = 2,
   ExcelConst_msoArrowheadLong = 3,
   _Excel_MsoArrowheadLengthForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoArrowheadStyle
{
   ExcelConst_msoArrowheadStyleMixed = -2,
   ExcelConst_msoArrowheadNone = 1,
   ExcelConst_msoArrowheadTriangle = 2,
   ExcelConst_msoArrowheadOpen = 3,
   ExcelConst_msoArrowheadStealth = 4,
   ExcelConst_msoArrowheadDiamond = 5,
   ExcelConst_msoArrowheadOval = 6,
   _Excel_MsoArrowheadStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoArrowheadWidth
{
   ExcelConst_msoArrowheadWidthMixed = -2,
   ExcelConst_msoArrowheadNarrow = 1,
   ExcelConst_msoArrowheadWidthMedium = 2,
   ExcelConst_msoArrowheadWide = 3,
   _Excel_MsoArrowheadWidthForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoLineDashStyle
{
   ExcelConst_msoLineDashStyleMixed = -2,
   ExcelConst_msoLineSolid = 1,
   ExcelConst_msoLineSquareDot = 2,
   ExcelConst_msoLineRoundDot = 3,
   ExcelConst_msoLineDash = 4,
   ExcelConst_msoLineDashDot = 5,
   ExcelConst_msoLineDashDotDot = 6,
   ExcelConst_msoLineLongDash = 7,
   ExcelConst_msoLineLongDashDot = 8,
   _Excel_MsoLineDashStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPatternType
{
   ExcelConst_msoPatternMixed = -2,
   ExcelConst_msoPattern5Percent = 1,
   ExcelConst_msoPattern10Percent = 2,
   ExcelConst_msoPattern20Percent = 3,
   ExcelConst_msoPattern25Percent = 4,
   ExcelConst_msoPattern30Percent = 5,
   ExcelConst_msoPattern40Percent = 6,
   ExcelConst_msoPattern50Percent = 7,
   ExcelConst_msoPattern60Percent = 8,
   ExcelConst_msoPattern70Percent = 9,
   ExcelConst_msoPattern75Percent = 10,
   ExcelConst_msoPattern80Percent = 11,
   ExcelConst_msoPattern90Percent = 12,
   ExcelConst_msoPatternDarkHorizontal = 13,
   ExcelConst_msoPatternDarkVertical = 14,
   ExcelConst_msoPatternDarkDownwardDiagonal = 15,
   ExcelConst_msoPatternDarkUpwardDiagonal = 16,
   ExcelConst_msoPatternSmallCheckerBoard = 17,
   ExcelConst_msoPatternTrellis = 18,
   ExcelConst_msoPatternLightHorizontal = 19,
   ExcelConst_msoPatternLightVertical = 20,
   ExcelConst_msoPatternLightDownwardDiagonal = 21,
   ExcelConst_msoPatternLightUpwardDiagonal = 22,
   ExcelConst_msoPatternSmallGrid = 23,
   ExcelConst_msoPatternDottedDiamond = 24,
   ExcelConst_msoPatternWideDownwardDiagonal = 25,
   ExcelConst_msoPatternWideUpwardDiagonal = 26,
   ExcelConst_msoPatternDashedUpwardDiagonal = 27,
   ExcelConst_msoPatternDashedDownwardDiagonal = 28,
   ExcelConst_msoPatternNarrowVertical = 29,
   ExcelConst_msoPatternNarrowHorizontal = 30,
   ExcelConst_msoPatternDashedVertical = 31,
   ExcelConst_msoPatternDashedHorizontal = 32,
   ExcelConst_msoPatternLargeConfetti = 33,
   ExcelConst_msoPatternLargeGrid = 34,
   ExcelConst_msoPatternHorizontalBrick = 35,
   ExcelConst_msoPatternLargeCheckerBoard = 36,
   ExcelConst_msoPatternSmallConfetti = 37,
   ExcelConst_msoPatternZigZag = 38,
   ExcelConst_msoPatternSolidDiamond = 39,
   ExcelConst_msoPatternDiagonalBrick = 40,
   ExcelConst_msoPatternOutlinedDiamond = 41,
   ExcelConst_msoPatternPlaid = 42,
   ExcelConst_msoPatternSphere = 43,
   ExcelConst_msoPatternWeave = 44,
   ExcelConst_msoPatternDottedGrid = 45,
   ExcelConst_msoPatternDivot = 46,
   ExcelConst_msoPatternShingle = 47,
   ExcelConst_msoPatternWave = 48,
   _Excel_MsoPatternTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoLineStyle
{
   ExcelConst_msoLineStyleMixed = -2,
   ExcelConst_msoLineSingle = 1,
   ExcelConst_msoLineThinThin = 2,
   ExcelConst_msoLineThinThick = 3,
   ExcelConst_msoLineThickThin = 4,
   ExcelConst_msoLineThickBetweenThin = 5,
   _Excel_MsoLineStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoEditingType
{
   ExcelConst_msoEditingAuto = 0,
   ExcelConst_msoEditingCorner = 1,
   ExcelConst_msoEditingSmooth = 2,
   ExcelConst_msoEditingSymmetric = 3,
   _Excel_MsoEditingTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoSegmentType
{
   ExcelConst_msoSegmentLine = 0,
   ExcelConst_msoSegmentCurve = 1,
   _Excel_MsoSegmentTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPictureColorType
{
   ExcelConst_msoPictureMixed = -2,
   ExcelConst_msoPictureAutomatic = 1,
   ExcelConst_msoPictureGrayscale = 2,
   ExcelConst_msoPictureBlackAndWhite = 3,
   ExcelConst_msoPictureWatermark = 4,
   _Excel_MsoPictureColorTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoShadowType
{
   ExcelConst_msoShadowMixed = -2,
   ExcelConst_msoShadow1 = 1,
   ExcelConst_msoShadow2 = 2,
   ExcelConst_msoShadow3 = 3,
   ExcelConst_msoShadow4 = 4,
   ExcelConst_msoShadow5 = 5,
   ExcelConst_msoShadow6 = 6,
   ExcelConst_msoShadow7 = 7,
   ExcelConst_msoShadow8 = 8,
   ExcelConst_msoShadow9 = 9,
   ExcelConst_msoShadow10 = 10,
   ExcelConst_msoShadow11 = 11,
   ExcelConst_msoShadow12 = 12,
   ExcelConst_msoShadow13 = 13,
   ExcelConst_msoShadow14 = 14,
   ExcelConst_msoShadow15 = 15,
   ExcelConst_msoShadow16 = 16,
   ExcelConst_msoShadow17 = 17,
   ExcelConst_msoShadow18 = 18,
   ExcelConst_msoShadow19 = 19,
   ExcelConst_msoShadow20 = 20,
   _Excel_MsoShadowTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoTextEffectAlignment
{
   ExcelConst_msoTextEffectAlignmentMixed = -2,
   ExcelConst_msoTextEffectAlignmentLeft = 1,
   ExcelConst_msoTextEffectAlignmentCentered = 2,
   ExcelConst_msoTextEffectAlignmentRight = 3,
   ExcelConst_msoTextEffectAlignmentLetterJustify = 4,
   ExcelConst_msoTextEffectAlignmentWordJustify = 5,
   ExcelConst_msoTextEffectAlignmentStretchJustify = 6,
   _Excel_MsoTextEffectAlignmentForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetTextEffectShape
{
   ExcelConst_msoTextEffectShapeMixed = -2,
   ExcelConst_msoTextEffectShapePlainText = 1,
   ExcelConst_msoTextEffectShapeStop = 2,
   ExcelConst_msoTextEffectShapeTriangleUp = 3,
   ExcelConst_msoTextEffectShapeTriangleDown = 4,
   ExcelConst_msoTextEffectShapeChevronUp = 5,
   ExcelConst_msoTextEffectShapeChevronDown = 6,
   ExcelConst_msoTextEffectShapeRingInside = 7,
   ExcelConst_msoTextEffectShapeRingOutside = 8,
   ExcelConst_msoTextEffectShapeArchUpCurve = 9,
   ExcelConst_msoTextEffectShapeArchDownCurve = 10,
   ExcelConst_msoTextEffectShapeCircleCurve = 11,
   ExcelConst_msoTextEffectShapeButtonCurve = 12,
   ExcelConst_msoTextEffectShapeArchUpPour = 13,
   ExcelConst_msoTextEffectShapeArchDownPour = 14,
   ExcelConst_msoTextEffectShapeCirclePour = 15,
   ExcelConst_msoTextEffectShapeButtonPour = 16,
   ExcelConst_msoTextEffectShapeCurveUp = 17,
   ExcelConst_msoTextEffectShapeCurveDown = 18,
   ExcelConst_msoTextEffectShapeCanUp = 19,
   ExcelConst_msoTextEffectShapeCanDown = 20,
   ExcelConst_msoTextEffectShapeWave1 = 21,
   ExcelConst_msoTextEffectShapeWave2 = 22,
   ExcelConst_msoTextEffectShapeDoubleWave1 = 23,
   ExcelConst_msoTextEffectShapeDoubleWave2 = 24,
   ExcelConst_msoTextEffectShapeInflate = 25,
   ExcelConst_msoTextEffectShapeDeflate = 26,
   ExcelConst_msoTextEffectShapeInflateBottom = 27,
   ExcelConst_msoTextEffectShapeDeflateBottom = 28,
   ExcelConst_msoTextEffectShapeInflateTop = 29,
   ExcelConst_msoTextEffectShapeDeflateTop = 30,
   ExcelConst_msoTextEffectShapeDeflateInflate = 31,
   ExcelConst_msoTextEffectShapeDeflateInflateDeflate = 32,
   ExcelConst_msoTextEffectShapeFadeRight = 33,
   ExcelConst_msoTextEffectShapeFadeLeft = 34,
   ExcelConst_msoTextEffectShapeFadeUp = 35,
   ExcelConst_msoTextEffectShapeFadeDown = 36,
   ExcelConst_msoTextEffectShapeSlantUp = 37,
   ExcelConst_msoTextEffectShapeSlantDown = 38,
   ExcelConst_msoTextEffectShapeCascadeUp = 39,
   ExcelConst_msoTextEffectShapeCascadeDown = 40,
   _Excel_MsoPresetTextEffectShapeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetTextEffect
{
   ExcelConst_msoTextEffectMixed = -2,
   ExcelConst_msoTextEffect1 = 0,
   ExcelConst_msoTextEffect2 = 1,
   ExcelConst_msoTextEffect3 = 2,
   ExcelConst_msoTextEffect4 = 3,
   ExcelConst_msoTextEffect5 = 4,
   ExcelConst_msoTextEffect6 = 5,
   ExcelConst_msoTextEffect7 = 6,
   ExcelConst_msoTextEffect8 = 7,
   ExcelConst_msoTextEffect9 = 8,
   ExcelConst_msoTextEffect10 = 9,
   ExcelConst_msoTextEffect11 = 10,
   ExcelConst_msoTextEffect12 = 11,
   ExcelConst_msoTextEffect13 = 12,
   ExcelConst_msoTextEffect14 = 13,
   ExcelConst_msoTextEffect15 = 14,
   ExcelConst_msoTextEffect16 = 15,
   ExcelConst_msoTextEffect17 = 16,
   ExcelConst_msoTextEffect18 = 17,
   ExcelConst_msoTextEffect19 = 18,
   ExcelConst_msoTextEffect20 = 19,
   ExcelConst_msoTextEffect21 = 20,
   ExcelConst_msoTextEffect22 = 21,
   ExcelConst_msoTextEffect23 = 22,
   ExcelConst_msoTextEffect24 = 23,
   ExcelConst_msoTextEffect25 = 24,
   ExcelConst_msoTextEffect26 = 25,
   ExcelConst_msoTextEffect27 = 26,
   ExcelConst_msoTextEffect28 = 27,
   ExcelConst_msoTextEffect29 = 28,
   ExcelConst_msoTextEffect30 = 29,
   _Excel_MsoPresetTextEffectForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetThreeDFormat
{
   ExcelConst_msoPresetThreeDFormatMixed = -2,
   ExcelConst_msoThreeD1 = 1,
   ExcelConst_msoThreeD2 = 2,
   ExcelConst_msoThreeD3 = 3,
   ExcelConst_msoThreeD4 = 4,
   ExcelConst_msoThreeD5 = 5,
   ExcelConst_msoThreeD6 = 6,
   ExcelConst_msoThreeD7 = 7,
   ExcelConst_msoThreeD8 = 8,
   ExcelConst_msoThreeD9 = 9,
   ExcelConst_msoThreeD10 = 10,
   ExcelConst_msoThreeD11 = 11,
   ExcelConst_msoThreeD12 = 12,
   ExcelConst_msoThreeD13 = 13,
   ExcelConst_msoThreeD14 = 14,
   ExcelConst_msoThreeD15 = 15,
   ExcelConst_msoThreeD16 = 16,
   ExcelConst_msoThreeD17 = 17,
   ExcelConst_msoThreeD18 = 18,
   ExcelConst_msoThreeD19 = 19,
   ExcelConst_msoThreeD20 = 20,
   _Excel_MsoPresetThreeDFormatForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetExtrusionDirection
{
   ExcelConst_msoPresetExtrusionDirectionMixed = -2,
   ExcelConst_msoExtrusionBottomRight = 1,
   ExcelConst_msoExtrusionBottom = 2,
   ExcelConst_msoExtrusionBottomLeft = 3,
   ExcelConst_msoExtrusionRight = 4,
   ExcelConst_msoExtrusionNone = 5,
   ExcelConst_msoExtrusionLeft = 6,
   ExcelConst_msoExtrusionTopRight = 7,
   ExcelConst_msoExtrusionTop = 8,
   ExcelConst_msoExtrusionTopLeft = 9,
   _Excel_MsoPresetExtrusionDirectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoExtrusionColorType
{
   ExcelConst_msoExtrusionColorTypeMixed = -2,
   ExcelConst_msoExtrusionColorAutomatic = 1,
   ExcelConst_msoExtrusionColorCustom = 2,
   _Excel_MsoExtrusionColorTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetLightingDirection
{
   ExcelConst_msoPresetLightingDirectionMixed = -2,
   ExcelConst_msoLightingTopLeft = 1,
   ExcelConst_msoLightingTop = 2,
   ExcelConst_msoLightingTopRight = 3,
   ExcelConst_msoLightingLeft = 4,
   ExcelConst_msoLightingNone = 5,
   ExcelConst_msoLightingRight = 6,
   ExcelConst_msoLightingBottomLeft = 7,
   ExcelConst_msoLightingBottom = 8,
   ExcelConst_msoLightingBottomRight = 9,
   _Excel_MsoPresetLightingDirectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetLightingSoftness
{
   ExcelConst_msoPresetLightingSoftnessMixed = -2,
   ExcelConst_msoLightingDim = 1,
   ExcelConst_msoLightingNormal = 2,
   ExcelConst_msoLightingBright = 3,
   _Excel_MsoPresetLightingSoftnessForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetMaterial
{
   ExcelConst_msoPresetMaterialMixed = -2,
   ExcelConst_msoMaterialMatte = 1,
   ExcelConst_msoMaterialPlastic = 2,
   ExcelConst_msoMaterialMetal = 3,
   ExcelConst_msoMaterialWireFrame = 4,
   _Excel_MsoPresetMaterialForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoGradientStyle
{
   ExcelConst_msoGradientMixed = -2,
   ExcelConst_msoGradientHorizontal = 1,
   ExcelConst_msoGradientVertical = 2,
   ExcelConst_msoGradientDiagonalUp = 3,
   ExcelConst_msoGradientDiagonalDown = 4,
   ExcelConst_msoGradientFromCorner = 5,
   ExcelConst_msoGradientFromTitle = 6,
   ExcelConst_msoGradientFromCenter = 7,
   _Excel_MsoGradientStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetGradientType
{
   ExcelConst_msoPresetGradientMixed = -2,
   ExcelConst_msoGradientEarlySunset = 1,
   ExcelConst_msoGradientLateSunset = 2,
   ExcelConst_msoGradientNightfall = 3,
   ExcelConst_msoGradientDaybreak = 4,
   ExcelConst_msoGradientHorizon = 5,
   ExcelConst_msoGradientDesert = 6,
   ExcelConst_msoGradientOcean = 7,
   ExcelConst_msoGradientCalmWater = 8,
   ExcelConst_msoGradientFire = 9,
   ExcelConst_msoGradientFog = 10,
   ExcelConst_msoGradientMoss = 11,
   ExcelConst_msoGradientPeacock = 12,
   ExcelConst_msoGradientWheat = 13,
   ExcelConst_msoGradientParchment = 14,
   ExcelConst_msoGradientMahogany = 15,
   ExcelConst_msoGradientRainbow = 16,
   ExcelConst_msoGradientRainbowII = 17,
   ExcelConst_msoGradientGold = 18,
   ExcelConst_msoGradientGoldII = 19,
   ExcelConst_msoGradientBrass = 20,
   ExcelConst_msoGradientChrome = 21,
   ExcelConst_msoGradientChromeII = 22,
   ExcelConst_msoGradientSilver = 23,
   ExcelConst_msoGradientSapphire = 24,
   _Excel_MsoPresetGradientTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoPresetTexture
{
   ExcelConst_msoPresetTextureMixed = -2,
   ExcelConst_msoTexturePapyrus = 1,
   ExcelConst_msoTextureCanvas = 2,
   ExcelConst_msoTextureDenim = 3,
   ExcelConst_msoTextureWovenMat = 4,
   ExcelConst_msoTextureWaterDroplets = 5,
   ExcelConst_msoTexturePaperBag = 6,
   ExcelConst_msoTextureFishFossil = 7,
   ExcelConst_msoTextureSand = 8,
   ExcelConst_msoTextureGreenMarble = 9,
   ExcelConst_msoTextureWhiteMarble = 10,
   ExcelConst_msoTextureBrownMarble = 11,
   ExcelConst_msoTextureGranite = 12,
   ExcelConst_msoTextureNewsprint = 13,
   ExcelConst_msoTextureRecycledPaper = 14,
   ExcelConst_msoTextureParchment = 15,
   ExcelConst_msoTextureStationery = 16,
   ExcelConst_msoTextureBlueTissuePaper = 17,
   ExcelConst_msoTexturePinkTissuePaper = 18,
   ExcelConst_msoTexturePurpleMesh = 19,
   ExcelConst_msoTextureBouquet = 20,
   ExcelConst_msoTextureCork = 21,
   ExcelConst_msoTextureWalnut = 22,
   ExcelConst_msoTextureOak = 23,
   ExcelConst_msoTextureMediumWood = 24,
   _Excel_MsoPresetTextureForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoGradientColorType
{
   ExcelConst_msoGradientColorMixed = -2,
   ExcelConst_msoGradientOneColor = 1,
   ExcelConst_msoGradientTwoColors = 2,
   ExcelConst_msoGradientPresetColors = 3,
   _Excel_MsoGradientColorTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoTextureType
{
   ExcelConst_msoTextureTypeMixed = -2,
   ExcelConst_msoTexturePreset = 1,
   ExcelConst_msoTextureUserDefined = 2,
   _Excel_MsoTextureTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoFillType
{
   ExcelConst_msoFillMixed = -2,
   ExcelConst_msoFillSolid = 1,
   ExcelConst_msoFillPatterned = 2,
   ExcelConst_msoFillGradient = 3,
   ExcelConst_msoFillTextured = 4,
   ExcelConst_msoFillBackground = 5,
   ExcelConst_msoFillPicture = 6,
   _Excel_MsoFillTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoDiagramNodeType
{
   ExcelConst_msoDiagramNode = 1,
   ExcelConst_msoDiagramAssistant = 2,
   _Excel_MsoDiagramNodeTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoRelativeNodePosition
{
   ExcelConst_msoBeforeNode = 1,
   ExcelConst_msoAfterNode = 2,
   ExcelConst_msoBeforeFirstSibling = 3,
   ExcelConst_msoAfterLastSibling = 4,
   _Excel_MsoRelativeNodePositionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoOrgChartLayoutType
{
   ExcelConst_msoOrgChartLayoutMixed = -2,
   ExcelConst_msoOrgChartLayoutStandard = 1,
   ExcelConst_msoOrgChartLayoutBothHanging = 2,
   ExcelConst_msoOrgChartLayoutLeftHanging = 3,
   ExcelConst_msoOrgChartLayoutRightHanging = 4,
   _Excel_MsoOrgChartLayoutTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFillWith
{
   ExcelConst_xlFillWithAll = -4104,
   ExcelConst_xlFillWithContents = 2,
   ExcelConst_xlFillWithFormats = -4122,
   _Excel_XlFillWithForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSourceType
{
   ExcelConst_xlSourceWorkbook = 0,
   ExcelConst_xlSourceSheet = 1,
   ExcelConst_xlSourcePrintArea = 2,
   ExcelConst_xlSourceAutoFilter = 3,
   ExcelConst_xlSourceRange = 4,
   ExcelConst_xlSourceChart = 5,
   ExcelConst_xlSourcePivotTable = 6,
   ExcelConst_xlSourceQuery = 7,
   _Excel_XlSourceTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlHtmlType
{
   ExcelConst_xlHtmlStatic = 0,
   ExcelConst_xlHtmlCalc = 1,
   ExcelConst_xlHtmlList = 2,
   ExcelConst_xlHtmlChart = 3,
   _Excel_XlHtmlTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoScreenSize
{
   ExcelConst_msoScreenSize544x376 = 0,
   ExcelConst_msoScreenSize640x480 = 1,
   ExcelConst_msoScreenSize720x512 = 2,
   ExcelConst_msoScreenSize800x600 = 3,
   ExcelConst_msoScreenSize1024x768 = 4,
   ExcelConst_msoScreenSize1152x882 = 5,
   ExcelConst_msoScreenSize1152x900 = 6,
   ExcelConst_msoScreenSize1280x1024 = 7,
   ExcelConst_msoScreenSize1600x1200 = 8,
   ExcelConst_msoScreenSize1800x1440 = 9,
   ExcelConst_msoScreenSize1920x1200 = 10,
   _Excel_MsoScreenSizeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoTargetBrowser
{
   ExcelConst_msoTargetBrowserV3 = 0,
   ExcelConst_msoTargetBrowserV4 = 1,
   ExcelConst_msoTargetBrowserIE4 = 2,
   ExcelConst_msoTargetBrowserIE5 = 3,
   ExcelConst_msoTargetBrowserIE6 = 4,
   _Excel_MsoTargetBrowserForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCubeFieldType
{
   ExcelConst_xlHierarchy = 1,
   ExcelConst_xlMeasure = 2,
   ExcelConst_xlSet = 3,
   _Excel_XlCubeFieldTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPivotFieldOrientation
{
   ExcelConst_xlColumnField = 2,
   ExcelConst_xlDataField = 4,
   ExcelConst_xlHidden = 0,
   ExcelConst_xlPageField = 3,
   ExcelConst_xlRowField = 1,
   _Excel_XlPivotFieldOrientationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLayoutFormType
{
   ExcelConst_xlTabular = 0,
   ExcelConst_xlOutline = 1,
   _Excel_XlLayoutFormTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSubtototalLocationType
{
   ExcelConst_xlAtTop = 1,
   ExcelConst_xlAtBottom = 2,
   _Excel_XlSubtototalLocationTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlColorIndex
{
   ExcelConst_xlColorIndexAutomatic = -4105,
   ExcelConst_xlColorIndexNone = -4142,
   _Excel_XlColorIndexForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlWindowType
{
   ExcelConst_xlChartAsWindow = 5,
   ExcelConst_xlChartInPlace = 4,
   ExcelConst_xlClipboard = 3,
   ExcelConst_xlInfo = -4129,
   ExcelConst_xlWorkbook = 1,
   _Excel_XlWindowTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlWindowView
{
   ExcelConst_xlNormalView = 1,
   ExcelConst_xlPageBreakPreview = 2,
   _Excel_XlWindowViewForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlArrangeStyle
{
   ExcelConst_xlArrangeStyleCascade = 7,
   ExcelConst_xlArrangeStyleHorizontal = -4128,
   ExcelConst_xlArrangeStyleTiled = 1,
   ExcelConst_xlArrangeStyleVertical = -4166,
   _Excel_XlArrangeStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFilterAction
{
   ExcelConst_xlFilterCopy = 2,
   ExcelConst_xlFilterInPlace = 1,
   _Excel_XlFilterActionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlApplyNamesOrder
{
   ExcelConst_xlColumnThenRow = 2,
   ExcelConst_xlRowThenColumn = 1,
   _Excel_XlApplyNamesOrderForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlAutoFillType
{
   ExcelConst_xlFillCopy = 1,
   ExcelConst_xlFillDays = 5,
   ExcelConst_xlFillDefault = 0,
   ExcelConst_xlFillFormats = 3,
   ExcelConst_xlFillMonths = 7,
   ExcelConst_xlFillSeries = 2,
   ExcelConst_xlFillValues = 4,
   ExcelConst_xlFillWeekdays = 6,
   ExcelConst_xlFillYears = 8,
   ExcelConst_xlGrowthTrend = 10,
   ExcelConst_xlLinearTrend = 9,
   _Excel_XlAutoFillTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlAutoFilterOperator
{
   ExcelConst_xlAnd = 1,
   ExcelConst_xlBottom10Items = 4,
   ExcelConst_xlBottom10Percent = 6,
   ExcelConst_xlOr = 2,
   ExcelConst_xlTop10Items = 3,
   ExcelConst_xlTop10Percent = 5,
   _Excel_XlAutoFilterOperatorForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlRangeAutoFormat
{
   ExcelConst_xlRangeAutoFormat3DEffects1 = 13,
   ExcelConst_xlRangeAutoFormat3DEffects2 = 14,
   ExcelConst_xlRangeAutoFormatAccounting1 = 4,
   ExcelConst_xlRangeAutoFormatAccounting2 = 5,
   ExcelConst_xlRangeAutoFormatAccounting3 = 6,
   ExcelConst_xlRangeAutoFormatAccounting4 = 17,
   ExcelConst_xlRangeAutoFormatClassic1 = 1,
   ExcelConst_xlRangeAutoFormatClassic2 = 2,
   ExcelConst_xlRangeAutoFormatClassic3 = 3,
   ExcelConst_xlRangeAutoFormatColor1 = 7,
   ExcelConst_xlRangeAutoFormatColor2 = 8,
   ExcelConst_xlRangeAutoFormatColor3 = 9,
   ExcelConst_xlRangeAutoFormatList1 = 10,
   ExcelConst_xlRangeAutoFormatList2 = 11,
   ExcelConst_xlRangeAutoFormatList3 = 12,
   ExcelConst_xlRangeAutoFormatLocalFormat1 = 15,
   ExcelConst_xlRangeAutoFormatLocalFormat2 = 16,
   ExcelConst_xlRangeAutoFormatLocalFormat3 = 19,
   ExcelConst_xlRangeAutoFormatLocalFormat4 = 20,
   ExcelConst_xlRangeAutoFormatReport1 = 21,
   ExcelConst_xlRangeAutoFormatReport2 = 22,
   ExcelConst_xlRangeAutoFormatReport3 = 23,
   ExcelConst_xlRangeAutoFormatReport4 = 24,
   ExcelConst_xlRangeAutoFormatReport5 = 25,
   ExcelConst_xlRangeAutoFormatReport6 = 26,
   ExcelConst_xlRangeAutoFormatReport7 = 27,
   ExcelConst_xlRangeAutoFormatReport8 = 28,
   ExcelConst_xlRangeAutoFormatReport9 = 29,
   ExcelConst_xlRangeAutoFormatReport10 = 30,
   ExcelConst_xlRangeAutoFormatClassicPivotTable = 31,
   ExcelConst_xlRangeAutoFormatTable1 = 32,
   ExcelConst_xlRangeAutoFormatTable2 = 33,
   ExcelConst_xlRangeAutoFormatTable3 = 34,
   ExcelConst_xlRangeAutoFormatTable4 = 35,
   ExcelConst_xlRangeAutoFormatTable5 = 36,
   ExcelConst_xlRangeAutoFormatTable6 = 37,
   ExcelConst_xlRangeAutoFormatTable7 = 38,
   ExcelConst_xlRangeAutoFormatTable8 = 39,
   ExcelConst_xlRangeAutoFormatTable9 = 40,
   ExcelConst_xlRangeAutoFormatTable10 = 41,
   ExcelConst_xlRangeAutoFormatPTNone = 42,
   ExcelConst_xlRangeAutoFormatNone = -4142,
   ExcelConst_xlRangeAutoFormatSimple = -4154,
   _Excel_XlRangeAutoFormatForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlBorderWeight
{
   ExcelConst_xlHairline = 1,
   ExcelConst_xlMedium = -4138,
   ExcelConst_xlThick = 4,
   ExcelConst_xlThin = 2,
   _Excel_XlBorderWeightForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDataSeriesType
{
   ExcelConst_xlAutoFill = 4,
   ExcelConst_xlChronological = 3,
   ExcelConst_xlGrowth = 2,
   ExcelConst_xlDataSeriesLinear = -4132,
   _Excel_XlDataSeriesTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDataSeriesDate
{
   ExcelConst_xlDay = 1,
   ExcelConst_xlMonth = 3,
   ExcelConst_xlWeekday = 2,
   ExcelConst_xlYear = 4,
   _Excel_XlDataSeriesDateForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlEditionType
{
   ExcelConst_xlPublisher = 1,
   ExcelConst_xlSubscriber = 2,
   _Excel_XlEditionTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlEditionOptionsOption
{
   ExcelConst_xlAutomaticUpdate = 4,
   ExcelConst_xlCancel = 1,
   ExcelConst_xlChangeAttributes = 6,
   ExcelConst_xlManualUpdate = 5,
   ExcelConst_xlOpenSource = 3,
   ExcelConst_xlSelect = 3,
   ExcelConst_xlSendPublisher = 2,
   ExcelConst_xlUpdateSubscriber = 2,
   _Excel_XlEditionOptionsOptionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSearchDirection
{
   ExcelConst_xlNext = 1,
   ExcelConst_xlPrevious = 2,
   _Excel_XlSearchDirectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFormulaLabel
{
   ExcelConst_xlNoLabels = -4142,
   ExcelConst_xlRowLabels = 1,
   ExcelConst_xlColumnLabels = 2,
   ExcelConst_xlMixedLabels = 3,
   _Excel_XlFormulaLabelForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLocationInTable
{
   ExcelConst_xlColumnHeader = -4110,
   ExcelConst_xlColumnItem = 5,
   ExcelConst_xlDataHeader = 3,
   ExcelConst_xlDataItem = 7,
   ExcelConst_xlPageHeader = 2,
   ExcelConst_xlPageItem = 6,
   ExcelConst_xlRowHeader = -4153,
   ExcelConst_xlRowItem = 4,
   ExcelConst_xlTableBody = 8,
   _Excel_XlLocationInTableForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPasteType
{
   ExcelConst_xlPasteAll = -4104,
   ExcelConst_xlPasteAllExceptBorders = 7,
   ExcelConst_xlPasteFormats = -4122,
   ExcelConst_xlPasteFormulas = -4123,
   ExcelConst_xlPasteComments = -4144,
   ExcelConst_xlPasteValues = -4163,
   ExcelConst_xlPasteColumnWidths = 8,
   ExcelConst_xlPasteValidation = 6,
   ExcelConst_xlPasteFormulasAndNumberFormats = 11,
   ExcelConst_xlPasteValuesAndNumberFormats = 12,
   _Excel_XlPasteTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPasteSpecialOperation
{
   ExcelConst_xlPasteSpecialOperationAdd = 2,
   ExcelConst_xlPasteSpecialOperationDivide = 5,
   ExcelConst_xlPasteSpecialOperationMultiply = 4,
   ExcelConst_xlPasteSpecialOperationNone = -4142,
   ExcelConst_xlPasteSpecialOperationSubtract = 3,
   _Excel_XlPasteSpecialOperationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSortOrder
{
   ExcelConst_xlAscending = 1,
   ExcelConst_xlDescending = 2,
   _Excel_XlSortOrderForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlYesNoGuess
{
   ExcelConst_xlGuess = 0,
   ExcelConst_xlNo = 2,
   ExcelConst_xlYes = 1,
   _Excel_XlYesNoGuessForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSortOrientation
{
   ExcelConst_xlSortRows = 2,
   ExcelConst_xlSortColumns = 1,
   _Excel_XlSortOrientationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSortMethod
{
   ExcelConst_xlPinYin = 1,
   ExcelConst_xlStroke = 2,
   _Excel_XlSortMethodForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSortDataOption
{
   ExcelConst_xlSortNormal = 0,
   ExcelConst_xlSortTextAsNumbers = 1,
   _Excel_XlSortDataOptionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCellType
{
   ExcelConst_xlCellTypeBlanks = 4,
   ExcelConst_xlCellTypeConstants = 2,
   ExcelConst_xlCellTypeFormulas = -4123,
   ExcelConst_xlCellTypeLastCell = 11,
   ExcelConst_xlCellTypeComments = -4144,
   ExcelConst_xlCellTypeVisible = 12,
   ExcelConst_xlCellTypeAllFormatConditions = -4172,
   ExcelConst_xlCellTypeSameFormatConditions = -4173,
   ExcelConst_xlCellTypeAllValidation = -4174,
   ExcelConst_xlCellTypeSameValidation = -4175,
   _Excel_XlCellTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSubscribeToFormat
{
   ExcelConst_xlSubscribeToPicture = -4147,
   ExcelConst_xlSubscribeToText = -4158,
   _Excel_XlSubscribeToFormatForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSummaryRow
{
   ExcelConst_xlSummaryAbove = 0,
   ExcelConst_xlSummaryBelow = 1,
   _Excel_XlSummaryRowForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPageBreak
{
   ExcelConst_xlPageBreakAutomatic = -4105,
   ExcelConst_xlPageBreakManual = -4135,
   ExcelConst_xlPageBreakNone = -4142,
   _Excel_XlPageBreakForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPageBreakExtent
{
   ExcelConst_xlPageBreakFull = 1,
   ExcelConst_xlPageBreakPartial = 2,
   _Excel_XlPageBreakExtentForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlHAlign
{
   ExcelConst_xlHAlignCenter = -4108,
   ExcelConst_xlHAlignCenterAcrossSelection = 7,
   ExcelConst_xlHAlignDistributed = -4117,
   ExcelConst_xlHAlignFill = 5,
   ExcelConst_xlHAlignGeneral = 1,
   ExcelConst_xlHAlignJustify = -4130,
   ExcelConst_xlHAlignLeft = -4131,
   ExcelConst_xlHAlignRight = -4152,
   _Excel_XlHAlignForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlOrientation
{
   ExcelConst_xlDownward = -4170,
   ExcelConst_xlHorizontal = -4128,
   ExcelConst_xlUpward = -4171,
   ExcelConst_xlVertical = -4166,
   _Excel_XlOrientationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlVAlign
{
   ExcelConst_xlVAlignBottom = -4107,
   ExcelConst_xlVAlignCenter = -4108,
   ExcelConst_xlVAlignDistributed = -4117,
   ExcelConst_xlVAlignJustify = -4130,
   ExcelConst_xlVAlignTop = -4160,
   _Excel_XlVAlignForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlBordersIndex
{
   ExcelConst_xlInsideHorizontal = 12,
   ExcelConst_xlInsideVertical = 11,
   ExcelConst_xlDiagonalDown = 5,
   ExcelConst_xlDiagonalUp = 6,
   ExcelConst_xlEdgeBottom = 9,
   ExcelConst_xlEdgeLeft = 7,
   ExcelConst_xlEdgeRight = 10,
   ExcelConst_xlEdgeTop = 8,
   _Excel_XlBordersIndexForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlToolbarProtection
{
   ExcelConst_xlNoButtonChanges = 1,
   ExcelConst_xlNoChanges = 4,
   ExcelConst_xlNoDockingChanges = 3,
   ExcelConst_xlToolbarProtectionNone = -4143,
   ExcelConst_xlNoShapeChanges = 2,
   _Excel_XlToolbarProtectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPivotTableSourceType
{
   ExcelConst_xlScenario = 4,
   ExcelConst_xlConsolidation = 3,
   ExcelConst_xlDatabase = 1,
   ExcelConst_xlExternal = 2,
   ExcelConst_xlPivotTable = -4148,
   _Excel_XlPivotTableSourceTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPivotTableMissingItems
{
   ExcelConst_xlMissingItemsDefault = -1,
   ExcelConst_xlMissingItemsNone = 0,
   ExcelConst_xlMissingItemsMax = 32500,
   _Excel_XlPivotTableMissingItemsForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPTSelectionMode
{
   ExcelConst_xlLabelOnly = 1,
   ExcelConst_xlDataAndLabel = 0,
   ExcelConst_xlDataOnly = 2,
   ExcelConst_xlOrigin = 3,
   ExcelConst_xlButton = 15,
   ExcelConst_xlBlanks = 4,
   ExcelConst_xlFirstRow = 256,
   _Excel_XlPTSelectionModeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPivotFormatType
{
   ExcelConst_xlReport1 = 0,
   ExcelConst_xlReport2 = 1,
   ExcelConst_xlReport3 = 2,
   ExcelConst_xlReport4 = 3,
   ExcelConst_xlReport5 = 4,
   ExcelConst_xlReport6 = 5,
   ExcelConst_xlReport7 = 6,
   ExcelConst_xlReport8 = 7,
   ExcelConst_xlReport9 = 8,
   ExcelConst_xlReport10 = 9,
   ExcelConst_xlTable1 = 10,
   ExcelConst_xlTable2 = 11,
   ExcelConst_xlTable3 = 12,
   ExcelConst_xlTable4 = 13,
   ExcelConst_xlTable5 = 14,
   ExcelConst_xlTable6 = 15,
   ExcelConst_xlTable7 = 16,
   ExcelConst_xlTable8 = 17,
   ExcelConst_xlTable9 = 18,
   ExcelConst_xlTable10 = 19,
   ExcelConst_xlPTClassic = 20,
   ExcelConst_xlPTNone = 21,
   _Excel_XlPivotFormatTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPivotTableVersionList
{
   ExcelConst_xlPivotTableVersion2000 = 0,
   ExcelConst_xlPivotTableVersion10 = 1,
   ExcelConst_xlPivotTableVersionCurrent = -1,
   _Excel_XlPivotTableVersionListForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPivotFieldCalculation
{
   ExcelConst_xlDifferenceFrom = 2,
   ExcelConst_xlIndex = 9,
   ExcelConst_xlNoAdditionalCalculation = -4143,
   ExcelConst_xlPercentDifferenceFrom = 4,
   ExcelConst_xlPercentOf = 3,
   ExcelConst_xlPercentOfColumn = 7,
   ExcelConst_xlPercentOfRow = 6,
   ExcelConst_xlPercentOfTotal = 8,
   ExcelConst_xlRunningTotal = 5,
   _Excel_XlPivotFieldCalculationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPivotFieldDataType
{
   ExcelConst_xlDate = 2,
   ExcelConst_xlNumber = -4145,
   ExcelConst_xlText = -4158,
   _Excel_XlPivotFieldDataTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlBuiltInDialog
{
   ExcelConst_xlDialogOpen = 1,
   ExcelConst_xlDialogOpenLinks = 2,
   ExcelConst_xlDialogSaveAs = 5,
   ExcelConst_xlDialogFileDelete = 6,
   ExcelConst_xlDialogPageSetup = 7,
   ExcelConst_xlDialogPrint = 8,
   ExcelConst_xlDialogPrinterSetup = 9,
   ExcelConst_xlDialogArrangeAll = 12,
   ExcelConst_xlDialogWindowSize = 13,
   ExcelConst_xlDialogWindowMove = 14,
   ExcelConst_xlDialogRun = 17,
   ExcelConst_xlDialogSetPrintTitles = 23,
   ExcelConst_xlDialogFont = 26,
   ExcelConst_xlDialogDisplay = 27,
   ExcelConst_xlDialogProtectDocument = 28,
   ExcelConst_xlDialogCalculation = 32,
   ExcelConst_xlDialogExtract = 35,
   ExcelConst_xlDialogDataDelete = 36,
   ExcelConst_xlDialogSort = 39,
   ExcelConst_xlDialogDataSeries = 40,
   ExcelConst_xlDialogTable = 41,
   ExcelConst_xlDialogFormatNumber = 42,
   ExcelConst_xlDialogAlignment = 43,
   ExcelConst_xlDialogStyle = 44,
   ExcelConst_xlDialogBorder = 45,
   ExcelConst_xlDialogCellProtection = 46,
   ExcelConst_xlDialogColumnWidth = 47,
   ExcelConst_xlDialogClear = 52,
   ExcelConst_xlDialogPasteSpecial = 53,
   ExcelConst_xlDialogEditDelete = 54,
   ExcelConst_xlDialogInsert = 55,
   ExcelConst_xlDialogPasteNames = 58,
   ExcelConst_xlDialogDefineName = 61,
   ExcelConst_xlDialogCreateNames = 62,
   ExcelConst_xlDialogFormulaGoto = 63,
   ExcelConst_xlDialogFormulaFind = 64,
   ExcelConst_xlDialogGalleryArea = 67,
   ExcelConst_xlDialogGalleryBar = 68,
   ExcelConst_xlDialogGalleryColumn = 69,
   ExcelConst_xlDialogGalleryLine = 70,
   ExcelConst_xlDialogGalleryPie = 71,
   ExcelConst_xlDialogGalleryScatter = 72,
   ExcelConst_xlDialogCombination = 73,
   ExcelConst_xlDialogGridlines = 76,
   ExcelConst_xlDialogAxes = 78,
   ExcelConst_xlDialogAttachText = 80,
   ExcelConst_xlDialogPatterns = 84,
   ExcelConst_xlDialogMainChart = 85,
   ExcelConst_xlDialogOverlay = 86,
   ExcelConst_xlDialogScale = 87,
   ExcelConst_xlDialogFormatLegend = 88,
   ExcelConst_xlDialogFormatText = 89,
   ExcelConst_xlDialogParse = 91,
   ExcelConst_xlDialogUnhide = 94,
   ExcelConst_xlDialogWorkspace = 95,
   ExcelConst_xlDialogActivate = 103,
   ExcelConst_xlDialogCopyPicture = 108,
   ExcelConst_xlDialogDeleteName = 110,
   ExcelConst_xlDialogDeleteFormat = 111,
   ExcelConst_xlDialogNew = 119,
   ExcelConst_xlDialogRowHeight = 127,
   ExcelConst_xlDialogFormatMove = 128,
   ExcelConst_xlDialogFormatSize = 129,
   ExcelConst_xlDialogFormulaReplace = 130,
   ExcelConst_xlDialogSelectSpecial = 132,
   ExcelConst_xlDialogApplyNames = 133,
   ExcelConst_xlDialogReplaceFont = 134,
   ExcelConst_xlDialogSplit = 137,
   ExcelConst_xlDialogOutline = 142,
   ExcelConst_xlDialogSaveWorkbook = 145,
   ExcelConst_xlDialogCopyChart = 147,
   ExcelConst_xlDialogFormatFont = 150,
   ExcelConst_xlDialogNote = 154,
   ExcelConst_xlDialogSetUpdateStatus = 159,
   ExcelConst_xlDialogColorPalette = 161,
   ExcelConst_xlDialogChangeLink = 166,
   ExcelConst_xlDialogAppMove = 170,
   ExcelConst_xlDialogAppSize = 171,
   ExcelConst_xlDialogMainChartType = 185,
   ExcelConst_xlDialogOverlayChartType = 186,
   ExcelConst_xlDialogOpenMail = 188,
   ExcelConst_xlDialogSendMail = 189,
   ExcelConst_xlDialogStandardFont = 190,
   ExcelConst_xlDialogConsolidate = 191,
   ExcelConst_xlDialogSortSpecial = 192,
   ExcelConst_xlDialogGallery3dArea = 193,
   ExcelConst_xlDialogGallery3dColumn = 194,
   ExcelConst_xlDialogGallery3dLine = 195,
   ExcelConst_xlDialogGallery3dPie = 196,
   ExcelConst_xlDialogView3d = 197,
   ExcelConst_xlDialogGoalSeek = 198,
   ExcelConst_xlDialogWorkgroup = 199,
   ExcelConst_xlDialogFillGroup = 200,
   ExcelConst_xlDialogUpdateLink = 201,
   ExcelConst_xlDialogPromote = 202,
   ExcelConst_xlDialogDemote = 203,
   ExcelConst_xlDialogShowDetail = 204,
   ExcelConst_xlDialogObjectProperties = 207,
   ExcelConst_xlDialogSaveNewObject = 208,
   ExcelConst_xlDialogApplyStyle = 212,
   ExcelConst_xlDialogAssignToObject = 213,
   ExcelConst_xlDialogObjectProtection = 214,
   ExcelConst_xlDialogCreatePublisher = 217,
   ExcelConst_xlDialogSubscribeTo = 218,
   ExcelConst_xlDialogShowToolbar = 220,
   ExcelConst_xlDialogPrintPreview = 222,
   ExcelConst_xlDialogEditColor = 223,
   ExcelConst_xlDialogFormatMain = 225,
   ExcelConst_xlDialogFormatOverlay = 226,
   ExcelConst_xlDialogEditSeries = 228,
   ExcelConst_xlDialogDefineStyle = 229,
   ExcelConst_xlDialogGalleryRadar = 249,
   ExcelConst_xlDialogEditionOptions = 251,
   ExcelConst_xlDialogZoom = 256,
   ExcelConst_xlDialogInsertObject = 259,
   ExcelConst_xlDialogSize = 261,
   ExcelConst_xlDialogMove = 262,
   ExcelConst_xlDialogFormatAuto = 269,
   ExcelConst_xlDialogGallery3dBar = 272,
   ExcelConst_xlDialogGallery3dSurface = 273,
   ExcelConst_xlDialogCustomizeToolbar = 276,
   ExcelConst_xlDialogWorkbookAdd = 281,
   ExcelConst_xlDialogWorkbookMove = 282,
   ExcelConst_xlDialogWorkbookCopy = 283,
   ExcelConst_xlDialogWorkbookOptions = 284,
   ExcelConst_xlDialogSaveWorkspace = 285,
   ExcelConst_xlDialogChartWizard = 288,
   ExcelConst_xlDialogAssignToTool = 293,
   ExcelConst_xlDialogPlacement = 300,
   ExcelConst_xlDialogFillWorkgroup = 301,
   ExcelConst_xlDialogWorkbookNew = 302,
   ExcelConst_xlDialogScenarioCells = 305,
   ExcelConst_xlDialogScenarioAdd = 307,
   ExcelConst_xlDialogScenarioEdit = 308,
   ExcelConst_xlDialogScenarioSummary = 311,
   ExcelConst_xlDialogPivotTableWizard = 312,
   ExcelConst_xlDialogPivotFieldProperties = 313,
   ExcelConst_xlDialogOptionsCalculation = 318,
   ExcelConst_xlDialogOptionsEdit = 319,
   ExcelConst_xlDialogOptionsView = 320,
   ExcelConst_xlDialogAddinManager = 321,
   ExcelConst_xlDialogMenuEditor = 322,
   ExcelConst_xlDialogAttachToolbars = 323,
   ExcelConst_xlDialogOptionsChart = 325,
   ExcelConst_xlDialogVbaInsertFile = 328,
   ExcelConst_xlDialogVbaProcedureDefinition = 330,
   ExcelConst_xlDialogRoutingSlip = 336,
   ExcelConst_xlDialogMailLogon = 339,
   ExcelConst_xlDialogInsertPicture = 342,
   ExcelConst_xlDialogGalleryDoughnut = 344,
   ExcelConst_xlDialogChartTrend = 350,
   ExcelConst_xlDialogWorkbookInsert = 354,
   ExcelConst_xlDialogOptionsTransition = 355,
   ExcelConst_xlDialogOptionsGeneral = 356,
   ExcelConst_xlDialogFilterAdvanced = 370,
   ExcelConst_xlDialogMailNextLetter = 378,
   ExcelConst_xlDialogDataLabel = 379,
   ExcelConst_xlDialogInsertTitle = 380,
   ExcelConst_xlDialogFontProperties = 381,
   ExcelConst_xlDialogMacroOptions = 382,
   ExcelConst_xlDialogWorkbookUnhide = 384,
   ExcelConst_xlDialogWorkbookName = 386,
   ExcelConst_xlDialogGalleryCustom = 388,
   ExcelConst_xlDialogAddChartAutoformat = 390,
   ExcelConst_xlDialogChartAddData = 392,
   ExcelConst_xlDialogTabOrder = 394,
   ExcelConst_xlDialogSubtotalCreate = 398,
   ExcelConst_xlDialogWorkbookTabSplit = 415,
   ExcelConst_xlDialogWorkbookProtect = 417,
   ExcelConst_xlDialogScrollbarProperties = 420,
   ExcelConst_xlDialogPivotShowPages = 421,
   ExcelConst_xlDialogTextToColumns = 422,
   ExcelConst_xlDialogFormatCharttype = 423,
   ExcelConst_xlDialogPivotFieldGroup = 433,
   ExcelConst_xlDialogPivotFieldUngroup = 434,
   ExcelConst_xlDialogCheckboxProperties = 435,
   ExcelConst_xlDialogLabelProperties = 436,
   ExcelConst_xlDialogListboxProperties = 437,
   ExcelConst_xlDialogEditboxProperties = 438,
   ExcelConst_xlDialogOpenText = 441,
   ExcelConst_xlDialogPushbuttonProperties = 445,
   ExcelConst_xlDialogFilter = 447,
   ExcelConst_xlDialogFunctionWizard = 450,
   ExcelConst_xlDialogSaveCopyAs = 456,
   ExcelConst_xlDialogOptionsListsAdd = 458,
   ExcelConst_xlDialogSeriesAxes = 460,
   ExcelConst_xlDialogSeriesX = 461,
   ExcelConst_xlDialogSeriesY = 462,
   ExcelConst_xlDialogErrorbarX = 463,
   ExcelConst_xlDialogErrorbarY = 464,
   ExcelConst_xlDialogFormatChart = 465,
   ExcelConst_xlDialogSeriesOrder = 466,
   ExcelConst_xlDialogMailEditMailer = 470,
   ExcelConst_xlDialogStandardWidth = 472,
   ExcelConst_xlDialogScenarioMerge = 473,
   ExcelConst_xlDialogProperties = 474,
   ExcelConst_xlDialogSummaryInfo = 474,
   ExcelConst_xlDialogFindFile = 475,
   ExcelConst_xlDialogActiveCellFont = 476,
   ExcelConst_xlDialogVbaMakeAddin = 478,
   ExcelConst_xlDialogFileSharing = 481,
   ExcelConst_xlDialogAutoCorrect = 485,
   ExcelConst_xlDialogCustomViews = 493,
   ExcelConst_xlDialogInsertNameLabel = 496,
   ExcelConst_xlDialogSeriesShape = 504,
   ExcelConst_xlDialogChartOptionsDataLabels = 505,
   ExcelConst_xlDialogChartOptionsDataTable = 506,
   ExcelConst_xlDialogSetBackgroundPicture = 509,
   ExcelConst_xlDialogDataValidation = 525,
   ExcelConst_xlDialogChartType = 526,
   ExcelConst_xlDialogChartLocation = 527,
   ExcelConst__xlDialogPhonetic = 538,
   ExcelConst_xlDialogChartSourceData = 540,
   ExcelConst__xlDialogChartSourceData = 541,
   ExcelConst_xlDialogSeriesOptions = 557,
   ExcelConst_xlDialogPivotTableOptions = 567,
   ExcelConst_xlDialogPivotSolveOrder = 568,
   ExcelConst_xlDialogPivotCalculatedField = 570,
   ExcelConst_xlDialogPivotCalculatedItem = 572,
   ExcelConst_xlDialogConditionalFormatting = 583,
   ExcelConst_xlDialogInsertHyperlink = 596,
   ExcelConst_xlDialogProtectSharing = 620,
   ExcelConst_xlDialogOptionsME = 647,
   ExcelConst_xlDialogPublishAsWebPage = 653,
   ExcelConst_xlDialogPhonetic = 656,
   ExcelConst_xlDialogNewWebQuery = 667,
   ExcelConst_xlDialogImportTextFile = 666,
   ExcelConst_xlDialogExternalDataProperties = 530,
   ExcelConst_xlDialogWebOptionsGeneral = 683,
   ExcelConst_xlDialogWebOptionsFiles = 684,
   ExcelConst_xlDialogWebOptionsPictures = 685,
   ExcelConst_xlDialogWebOptionsEncoding = 686,
   ExcelConst_xlDialogWebOptionsFonts = 687,
   ExcelConst_xlDialogPivotClientServerSet = 689,
   ExcelConst_xlDialogPropertyFields = 754,
   ExcelConst_xlDialogSearch = 731,
   ExcelConst_xlDialogEvaluateFormula = 709,
   ExcelConst_xlDialogDataLabelMultiple = 723,
   ExcelConst_xlDialogChartOptionsDataLabelMultiple = 724,
   ExcelConst_xlDialogErrorChecking = 732,
   ExcelConst_xlDialogWebOptionsBrowsers = 773,
   ExcelConst_xlDialogCreateList = 796,
   ExcelConst_xlDialogPermission = 832,
   ExcelConst_xlDialogMyPermission = 834,
   _Excel_XlBuiltInDialogForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSummaryReportType
{
   ExcelConst_xlSummaryPivotTable = -4148,
   ExcelConst_xlStandardSummary = 1,
   _Excel_XlSummaryReportTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlRoutingSlipDelivery
{
   ExcelConst_xlAllAtOnce = 2,
   ExcelConst_xlOneAfterAnother = 1,
   _Excel_XlRoutingSlipDeliveryForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlRoutingSlipStatus
{
   ExcelConst_xlNotYetRouted = 0,
   ExcelConst_xlRoutingComplete = 2,
   ExcelConst_xlRoutingInProgress = 1,
   _Excel_XlRoutingSlipStatusForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSummaryColumn
{
   ExcelConst_xlSummaryOnLeft = -4131,
   ExcelConst_xlSummaryOnRight = -4152,
   _Excel_XlSummaryColumnForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlObjectSize
{
   ExcelConst_xlFitToPage = 2,
   ExcelConst_xlFullPage = 3,
   ExcelConst_xlScreenSize = 1,
   _Excel_XlObjectSizeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlOrder
{
   ExcelConst_xlDownThenOver = 1,
   ExcelConst_xlOverThenDown = 2,
   _Excel_XlOrderForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPageOrientation
{
   ExcelConst_xlLandscape = 2,
   ExcelConst_xlPortrait = 1,
   _Excel_XlPageOrientationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPaperSize
{
   ExcelConst_xlPaper10x14 = 16,
   ExcelConst_xlPaper11x17 = 17,
   ExcelConst_xlPaperA3 = 8,
   ExcelConst_xlPaperA4 = 9,
   ExcelConst_xlPaperA4Small = 10,
   ExcelConst_xlPaperA5 = 11,
   ExcelConst_xlPaperB4 = 12,
   ExcelConst_xlPaperB5 = 13,
   ExcelConst_xlPaperCsheet = 24,
   ExcelConst_xlPaperDsheet = 25,
   ExcelConst_xlPaperEnvelope10 = 20,
   ExcelConst_xlPaperEnvelope11 = 21,
   ExcelConst_xlPaperEnvelope12 = 22,
   ExcelConst_xlPaperEnvelope14 = 23,
   ExcelConst_xlPaperEnvelope9 = 19,
   ExcelConst_xlPaperEnvelopeB4 = 33,
   ExcelConst_xlPaperEnvelopeB5 = 34,
   ExcelConst_xlPaperEnvelopeB6 = 35,
   ExcelConst_xlPaperEnvelopeC3 = 29,
   ExcelConst_xlPaperEnvelopeC4 = 30,
   ExcelConst_xlPaperEnvelopeC5 = 28,
   ExcelConst_xlPaperEnvelopeC6 = 31,
   ExcelConst_xlPaperEnvelopeC65 = 32,
   ExcelConst_xlPaperEnvelopeDL = 27,
   ExcelConst_xlPaperEnvelopeItaly = 36,
   ExcelConst_xlPaperEnvelopeMonarch = 37,
   ExcelConst_xlPaperEnvelopePersonal = 38,
   ExcelConst_xlPaperEsheet = 26,
   ExcelConst_xlPaperExecutive = 7,
   ExcelConst_xlPaperFanfoldLegalGerman = 41,
   ExcelConst_xlPaperFanfoldStdGerman = 40,
   ExcelConst_xlPaperFanfoldUS = 39,
   ExcelConst_xlPaperFolio = 14,
   ExcelConst_xlPaperLedger = 4,
   ExcelConst_xlPaperLegal = 5,
   ExcelConst_xlPaperLetter = 1,
   ExcelConst_xlPaperLetterSmall = 2,
   ExcelConst_xlPaperNote = 18,
   ExcelConst_xlPaperQuarto = 15,
   ExcelConst_xlPaperStatement = 6,
   ExcelConst_xlPaperTabloid = 3,
   ExcelConst_xlPaperUser = 256,
   _Excel_XlPaperSizeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPrintLocation
{
   ExcelConst_xlPrintSheetEnd = 1,
   ExcelConst_xlPrintInPlace = 16,
   ExcelConst_xlPrintNoComments = -4142,
   _Excel_XlPrintLocationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPrintErrors
{
   ExcelConst_xlPrintErrorsDisplayed = 0,
   ExcelConst_xlPrintErrorsBlank = 1,
   ExcelConst_xlPrintErrorsDash = 2,
   ExcelConst_xlPrintErrorsNA = 3,
   _Excel_XlPrintErrorsForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlXLMMacroType
{
   ExcelConst_xlCommand = 2,
   ExcelConst_xlFunction = 1,
   ExcelConst_xlNotXLM = 3,
   _Excel_XlXLMMacroTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFormatConditionType
{
   ExcelConst_xlCellValue = 1,
   ExcelConst_xlExpression = 2,
   _Excel_XlFormatConditionTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlParameterDataType
{
   ExcelConst_xlParamTypeUnknown = 0,
   ExcelConst_xlParamTypeChar = 1,
   ExcelConst_xlParamTypeNumeric = 2,
   ExcelConst_xlParamTypeDecimal = 3,
   ExcelConst_xlParamTypeInteger = 4,
   ExcelConst_xlParamTypeSmallInt = 5,
   ExcelConst_xlParamTypeFloat = 6,
   ExcelConst_xlParamTypeReal = 7,
   ExcelConst_xlParamTypeDouble = 8,
   ExcelConst_xlParamTypeVarChar = 12,
   ExcelConst_xlParamTypeDate = 9,
   ExcelConst_xlParamTypeTime = 10,
   ExcelConst_xlParamTypeTimestamp = 11,
   ExcelConst_xlParamTypeLongVarChar = -1,
   ExcelConst_xlParamTypeBinary = -2,
   ExcelConst_xlParamTypeVarBinary = -3,
   ExcelConst_xlParamTypeLongVarBinary = -4,
   ExcelConst_xlParamTypeBigInt = -5,
   ExcelConst_xlParamTypeTinyInt = -6,
   ExcelConst_xlParamTypeBit = -7,
   ExcelConst_xlParamTypeWChar = -8,
   _Excel_XlParameterDataTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlParameterType
{
   ExcelConst_xlPrompt = 0,
   ExcelConst_xlConstant = 1,
   ExcelConst_xlRange = 2,
   _Excel_XlParameterTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDVType
{
   ExcelConst_xlValidateInputOnly = 0,
   ExcelConst_xlValidateWholeNumber = 1,
   ExcelConst_xlValidateDecimal = 2,
   ExcelConst_xlValidateList = 3,
   ExcelConst_xlValidateDate = 4,
   ExcelConst_xlValidateTime = 5,
   ExcelConst_xlValidateTextLength = 6,
   ExcelConst_xlValidateCustom = 7,
   _Excel_XlDVTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlAxisCrosses
{
   ExcelConst_xlAxisCrossesAutomatic = -4105,
   ExcelConst_xlAxisCrossesCustom = -4114,
   ExcelConst_xlAxisCrossesMaximum = 2,
   ExcelConst_xlAxisCrossesMinimum = 4,
   _Excel_XlAxisCrossesForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTickMark
{
   ExcelConst_xlTickMarkCross = 4,
   ExcelConst_xlTickMarkInside = 2,
   ExcelConst_xlTickMarkNone = -4142,
   ExcelConst_xlTickMarkOutside = 3,
   _Excel_XlTickMarkForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlScaleType
{
   ExcelConst_xlScaleLinear = -4132,
   ExcelConst_xlScaleLogarithmic = -4133,
   _Excel_XlScaleTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTickLabelPosition
{
   ExcelConst_xlTickLabelPositionHigh = -4127,
   ExcelConst_xlTickLabelPositionLow = -4134,
   ExcelConst_xlTickLabelPositionNextToAxis = 4,
   ExcelConst_xlTickLabelPositionNone = -4142,
   _Excel_XlTickLabelPositionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlAxisType
{
   ExcelConst_xlCategory = 1,
   ExcelConst_xlSeriesAxis = 3,
   ExcelConst_xlValue = 2,
   _Excel_XlAxisTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTimeUnit
{
   ExcelConst_xlDays = 0,
   ExcelConst_xlMonths = 1,
   ExcelConst_xlYears = 2,
   _Excel_XlTimeUnitForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCategoryType
{
   ExcelConst_xlCategoryScale = 2,
   ExcelConst_xlTimeScale = 3,
   ExcelConst_xlAutomaticScale = -4105,
   _Excel_XlCategoryTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDisplayUnit
{
   ExcelConst_xlHundreds = -2,
   ExcelConst_xlThousands = -3,
   ExcelConst_xlTenThousands = -4,
   ExcelConst_xlHundredThousands = -5,
   ExcelConst_xlMillions = -6,
   ExcelConst_xlTenMillions = -7,
   ExcelConst_xlHundredMillions = -8,
   ExcelConst_xlThousandMillions = -9,
   ExcelConst_xlMillionMillions = -10,
   _Excel_XlDisplayUnitForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSizeRepresents
{
   ExcelConst_xlSizeIsWidth = 2,
   ExcelConst_xlSizeIsArea = 1,
   _Excel_XlSizeRepresentsForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlChartSplitType
{
   ExcelConst_xlSplitByPosition = 1,
   ExcelConst_xlSplitByPercentValue = 3,
   ExcelConst_xlSplitByCustomSplit = 4,
   ExcelConst_xlSplitByValue = 2,
   _Excel_XlChartSplitTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlMarkerStyle
{
   ExcelConst_xlMarkerStyleAutomatic = -4105,
   ExcelConst_xlMarkerStyleCircle = 8,
   ExcelConst_xlMarkerStyleDash = -4115,
   ExcelConst_xlMarkerStyleDiamond = 2,
   ExcelConst_xlMarkerStyleDot = -4118,
   ExcelConst_xlMarkerStyleNone = -4142,
   ExcelConst_xlMarkerStylePicture = -4147,
   ExcelConst_xlMarkerStylePlus = 9,
   ExcelConst_xlMarkerStyleSquare = 1,
   ExcelConst_xlMarkerStyleStar = 5,
   ExcelConst_xlMarkerStyleTriangle = 3,
   ExcelConst_xlMarkerStyleX = -4168,
   _Excel_XlMarkerStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlChartPictureType
{
   ExcelConst_xlStackScale = 3,
   ExcelConst_xlStack = 2,
   ExcelConst_xlStretch = 1,
   _Excel_XlChartPictureTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlErrorBarDirection
{
   ExcelConst_xlX = -4168,
   ExcelConst_xlY = 1,
   _Excel_XlErrorBarDirectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlErrorBarInclude
{
   ExcelConst_xlErrorBarIncludeBoth = 1,
   ExcelConst_xlErrorBarIncludeMinusValues = 3,
   ExcelConst_xlErrorBarIncludeNone = -4142,
   ExcelConst_xlErrorBarIncludePlusValues = 2,
   _Excel_XlErrorBarIncludeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlErrorBarType
{
   ExcelConst_xlErrorBarTypeCustom = -4114,
   ExcelConst_xlErrorBarTypeFixedValue = 1,
   ExcelConst_xlErrorBarTypePercent = 2,
   ExcelConst_xlErrorBarTypeStDev = -4155,
   ExcelConst_xlErrorBarTypeStError = 4,
   _Excel_XlErrorBarTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDataLabelPosition
{
   ExcelConst_xlLabelPositionCenter = -4108,
   ExcelConst_xlLabelPositionAbove = 0,
   ExcelConst_xlLabelPositionBelow = 1,
   ExcelConst_xlLabelPositionLeft = -4131,
   ExcelConst_xlLabelPositionRight = -4152,
   ExcelConst_xlLabelPositionOutsideEnd = 2,
   ExcelConst_xlLabelPositionInsideEnd = 3,
   ExcelConst_xlLabelPositionInsideBase = 4,
   ExcelConst_xlLabelPositionBestFit = 5,
   ExcelConst_xlLabelPositionMixed = 6,
   ExcelConst_xlLabelPositionCustom = 7,
   _Excel_XlDataLabelPositionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTrendlineType
{
   ExcelConst_xlExponential = 5,
   ExcelConst_xlLinear = -4132,
   ExcelConst_xlLogarithmic = -4133,
   ExcelConst_xlMovingAvg = 6,
   ExcelConst_xlPolynomial = 3,
   ExcelConst_xlPower = 4,
   _Excel_XlTrendlineTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTickLabelOrientation
{
   ExcelConst_xlTickLabelOrientationAutomatic = -4105,
   ExcelConst_xlTickLabelOrientationDownward = -4170,
   ExcelConst_xlTickLabelOrientationHorizontal = -4128,
   ExcelConst_xlTickLabelOrientationUpward = -4171,
   ExcelConst_xlTickLabelOrientationVertical = -4166,
   _Excel_XlTickLabelOrientationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLegendPosition
{
   ExcelConst_xlLegendPositionBottom = -4107,
   ExcelConst_xlLegendPositionCorner = 2,
   ExcelConst_xlLegendPositionLeft = -4131,
   ExcelConst_xlLegendPositionRight = -4152,
   ExcelConst_xlLegendPositionTop = -4160,
   _Excel_XlLegendPositionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlEndStyleCap
{
   ExcelConst_xlCap = 1,
   ExcelConst_xlNoCap = 2,
   _Excel_XlEndStyleCapForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoFlipCmd
{
   ExcelConst_msoFlipHorizontal = 0,
   ExcelConst_msoFlipVertical = 1,
   _Excel_MsoFlipCmdForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoZOrderCmd
{
   ExcelConst_msoBringToFront = 0,
   ExcelConst_msoSendToBack = 1,
   ExcelConst_msoBringForward = 2,
   ExcelConst_msoSendBackward = 3,
   ExcelConst_msoBringInFrontOfText = 4,
   ExcelConst_msoSendBehindText = 5,
   _Excel_MsoZOrderCmdForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoAutoShapeType
{
   ExcelConst_msoShapeMixed = -2,
   ExcelConst_msoShapeRectangle = 1,
   ExcelConst_msoShapeParallelogram = 2,
   ExcelConst_msoShapeTrapezoid = 3,
   ExcelConst_msoShapeDiamond = 4,
   ExcelConst_msoShapeRoundedRectangle = 5,
   ExcelConst_msoShapeOctagon = 6,
   ExcelConst_msoShapeIsoscelesTriangle = 7,
   ExcelConst_msoShapeRightTriangle = 8,
   ExcelConst_msoShapeOval = 9,
   ExcelConst_msoShapeHexagon = 10,
   ExcelConst_msoShapeCross = 11,
   ExcelConst_msoShapeRegularPentagon = 12,
   ExcelConst_msoShapeCan = 13,
   ExcelConst_msoShapeCube = 14,
   ExcelConst_msoShapeBevel = 15,
   ExcelConst_msoShapeFoldedCorner = 16,
   ExcelConst_msoShapeSmileyFace = 17,
   ExcelConst_msoShapeDonut = 18,
   ExcelConst_msoShapeNoSymbol = 19,
   ExcelConst_msoShapeBlockArc = 20,
   ExcelConst_msoShapeHeart = 21,
   ExcelConst_msoShapeLightningBolt = 22,
   ExcelConst_msoShapeSun = 23,
   ExcelConst_msoShapeMoon = 24,
   ExcelConst_msoShapeArc = 25,
   ExcelConst_msoShapeDoubleBracket = 26,
   ExcelConst_msoShapeDoubleBrace = 27,
   ExcelConst_msoShapePlaque = 28,
   ExcelConst_msoShapeLeftBracket = 29,
   ExcelConst_msoShapeRightBracket = 30,
   ExcelConst_msoShapeLeftBrace = 31,
   ExcelConst_msoShapeRightBrace = 32,
   ExcelConst_msoShapeRightArrow = 33,
   ExcelConst_msoShapeLeftArrow = 34,
   ExcelConst_msoShapeUpArrow = 35,
   ExcelConst_msoShapeDownArrow = 36,
   ExcelConst_msoShapeLeftRightArrow = 37,
   ExcelConst_msoShapeUpDownArrow = 38,
   ExcelConst_msoShapeQuadArrow = 39,
   ExcelConst_msoShapeLeftRightUpArrow = 40,
   ExcelConst_msoShapeBentArrow = 41,
   ExcelConst_msoShapeUTurnArrow = 42,
   ExcelConst_msoShapeLeftUpArrow = 43,
   ExcelConst_msoShapeBentUpArrow = 44,
   ExcelConst_msoShapeCurvedRightArrow = 45,
   ExcelConst_msoShapeCurvedLeftArrow = 46,
   ExcelConst_msoShapeCurvedUpArrow = 47,
   ExcelConst_msoShapeCurvedDownArrow = 48,
   ExcelConst_msoShapeStripedRightArrow = 49,
   ExcelConst_msoShapeNotchedRightArrow = 50,
   ExcelConst_msoShapePentagon = 51,
   ExcelConst_msoShapeChevron = 52,
   ExcelConst_msoShapeRightArrowCallout = 53,
   ExcelConst_msoShapeLeftArrowCallout = 54,
   ExcelConst_msoShapeUpArrowCallout = 55,
   ExcelConst_msoShapeDownArrowCallout = 56,
   ExcelConst_msoShapeLeftRightArrowCallout = 57,
   ExcelConst_msoShapeUpDownArrowCallout = 58,
   ExcelConst_msoShapeQuadArrowCallout = 59,
   ExcelConst_msoShapeCircularArrow = 60,
   ExcelConst_msoShapeFlowchartProcess = 61,
   ExcelConst_msoShapeFlowchartAlternateProcess = 62,
   ExcelConst_msoShapeFlowchartDecision = 63,
   ExcelConst_msoShapeFlowchartData = 64,
   ExcelConst_msoShapeFlowchartPredefinedProcess = 65,
   ExcelConst_msoShapeFlowchartInternalStorage = 66,
   ExcelConst_msoShapeFlowchartDocument = 67,
   ExcelConst_msoShapeFlowchartMultidocument = 68,
   ExcelConst_msoShapeFlowchartTerminator = 69,
   ExcelConst_msoShapeFlowchartPreparation = 70,
   ExcelConst_msoShapeFlowchartManualInput = 71,
   ExcelConst_msoShapeFlowchartManualOperation = 72,
   ExcelConst_msoShapeFlowchartConnector = 73,
   ExcelConst_msoShapeFlowchartOffpageConnector = 74,
   ExcelConst_msoShapeFlowchartCard = 75,
   ExcelConst_msoShapeFlowchartPunchedTape = 76,
   ExcelConst_msoShapeFlowchartSummingJunction = 77,
   ExcelConst_msoShapeFlowchartOr = 78,
   ExcelConst_msoShapeFlowchartCollate = 79,
   ExcelConst_msoShapeFlowchartSort = 80,
   ExcelConst_msoShapeFlowchartExtract = 81,
   ExcelConst_msoShapeFlowchartMerge = 82,
   ExcelConst_msoShapeFlowchartStoredData = 83,
   ExcelConst_msoShapeFlowchartDelay = 84,
   ExcelConst_msoShapeFlowchartSequentialAccessStorage = 85,
   ExcelConst_msoShapeFlowchartMagneticDisk = 86,
   ExcelConst_msoShapeFlowchartDirectAccessStorage = 87,
   ExcelConst_msoShapeFlowchartDisplay = 88,
   ExcelConst_msoShapeExplosion1 = 89,
   ExcelConst_msoShapeExplosion2 = 90,
   ExcelConst_msoShape4pointStar = 91,
   ExcelConst_msoShape5pointStar = 92,
   ExcelConst_msoShape8pointStar = 93,
   ExcelConst_msoShape16pointStar = 94,
   ExcelConst_msoShape24pointStar = 95,
   ExcelConst_msoShape32pointStar = 96,
   ExcelConst_msoShapeUpRibbon = 97,
   ExcelConst_msoShapeDownRibbon = 98,
   ExcelConst_msoShapeCurvedUpRibbon = 99,
   ExcelConst_msoShapeCurvedDownRibbon = 100,
   ExcelConst_msoShapeVerticalScroll = 101,
   ExcelConst_msoShapeHorizontalScroll = 102,
   ExcelConst_msoShapeWave = 103,
   ExcelConst_msoShapeDoubleWave = 104,
   ExcelConst_msoShapeRectangularCallout = 105,
   ExcelConst_msoShapeRoundedRectangularCallout = 106,
   ExcelConst_msoShapeOvalCallout = 107,
   ExcelConst_msoShapeCloudCallout = 108,
   ExcelConst_msoShapeLineCallout1 = 109,
   ExcelConst_msoShapeLineCallout2 = 110,
   ExcelConst_msoShapeLineCallout3 = 111,
   ExcelConst_msoShapeLineCallout4 = 112,
   ExcelConst_msoShapeLineCallout1AccentBar = 113,
   ExcelConst_msoShapeLineCallout2AccentBar = 114,
   ExcelConst_msoShapeLineCallout3AccentBar = 115,
   ExcelConst_msoShapeLineCallout4AccentBar = 116,
   ExcelConst_msoShapeLineCallout1NoBorder = 117,
   ExcelConst_msoShapeLineCallout2NoBorder = 118,
   ExcelConst_msoShapeLineCallout3NoBorder = 119,
   ExcelConst_msoShapeLineCallout4NoBorder = 120,
   ExcelConst_msoShapeLineCallout1BorderandAccentBar = 121,
   ExcelConst_msoShapeLineCallout2BorderandAccentBar = 122,
   ExcelConst_msoShapeLineCallout3BorderandAccentBar = 123,
   ExcelConst_msoShapeLineCallout4BorderandAccentBar = 124,
   ExcelConst_msoShapeActionButtonCustom = 125,
   ExcelConst_msoShapeActionButtonHome = 126,
   ExcelConst_msoShapeActionButtonHelp = 127,
   ExcelConst_msoShapeActionButtonInformation = 128,
   ExcelConst_msoShapeActionButtonBackorPrevious = 129,
   ExcelConst_msoShapeActionButtonForwardorNext = 130,
   ExcelConst_msoShapeActionButtonBeginning = 131,
   ExcelConst_msoShapeActionButtonEnd = 132,
   ExcelConst_msoShapeActionButtonReturn = 133,
   ExcelConst_msoShapeActionButtonDocument = 134,
   ExcelConst_msoShapeActionButtonSound = 135,
   ExcelConst_msoShapeActionButtonMovie = 136,
   ExcelConst_msoShapeBalloon = 137,
   ExcelConst_msoShapeNotPrimitive = 138,
   _Excel_MsoAutoShapeTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoShapeType
{
   ExcelConst_msoShapeTypeMixed = -2,
   ExcelConst_msoAutoShape = 1,
   ExcelConst_msoCallout = 2,
   ExcelConst_msoChart = 3,
   ExcelConst_msoComment = 4,
   ExcelConst_msoFreeform = 5,
   ExcelConst_msoGroup = 6,
   ExcelConst_msoEmbeddedOLEObject = 7,
   ExcelConst_msoFormControl = 8,
   ExcelConst_msoLine = 9,
   ExcelConst_msoLinkedOLEObject = 10,
   ExcelConst_msoLinkedPicture = 11,
   ExcelConst_msoOLEControlObject = 12,
   ExcelConst_msoPicture = 13,
   ExcelConst_msoPlaceholder = 14,
   ExcelConst_msoTextEffect = 15,
   ExcelConst_msoMedia = 16,
   ExcelConst_msoTextBox = 17,
   ExcelConst_msoScriptAnchor = 18,
   ExcelConst_msoTable = 19,
   ExcelConst_msoCanvas = 20,
   ExcelConst_msoDiagram = 21,
   ExcelConst_msoInk = 22,
   ExcelConst_msoInkComment = 23,
   _Excel_MsoShapeTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoBlackWhiteMode
{
   ExcelConst_msoBlackWhiteMixed = -2,
   ExcelConst_msoBlackWhiteAutomatic = 1,
   ExcelConst_msoBlackWhiteGrayScale = 2,
   ExcelConst_msoBlackWhiteLightGrayScale = 3,
   ExcelConst_msoBlackWhiteInverseGrayScale = 4,
   ExcelConst_msoBlackWhiteGrayOutline = 5,
   ExcelConst_msoBlackWhiteBlackTextAndLine = 6,
   ExcelConst_msoBlackWhiteHighContrast = 7,
   ExcelConst_msoBlackWhiteBlack = 8,
   ExcelConst_msoBlackWhiteWhite = 9,
   ExcelConst_msoBlackWhiteDontShow = 10,
   _Excel_MsoBlackWhiteModeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPlacement
{
   ExcelConst_xlFreeFloating = 3,
   ExcelConst_xlMove = 2,
   ExcelConst_xlMoveAndSize = 1,
   _Excel_XlPlacementForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFormControl
{
   ExcelConst_xlButtonControl = 0,
   ExcelConst_xlCheckBox = 1,
   ExcelConst_xlDropDown = 2,
   ExcelConst_xlEditBox = 3,
   ExcelConst_xlGroupBox = 4,
   ExcelConst_xlLabel = 5,
   ExcelConst_xlListBox = 6,
   ExcelConst_xlOptionButton = 7,
   ExcelConst_xlScrollBar = 8,
   ExcelConst_xlSpinner = 9,
   _Excel_XlFormControlForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoConnectorType
{
   ExcelConst_msoConnectorTypeMixed = -2,
   ExcelConst_msoConnectorStraight = 1,
   ExcelConst_msoConnectorElbow = 2,
   ExcelConst_msoConnectorCurve = 3,
   _Excel_MsoConnectorTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoTextOrientation
{
   ExcelConst_msoTextOrientationMixed = -2,
   ExcelConst_msoTextOrientationHorizontal = 1,
   ExcelConst_msoTextOrientationUpward = 2,
   ExcelConst_msoTextOrientationDownward = 3,
   ExcelConst_msoTextOrientationVerticalFarEast = 4,
   ExcelConst_msoTextOrientationVertical = 5,
   ExcelConst_msoTextOrientationHorizontalRotatedFarEast = 6,
   _Excel_MsoTextOrientationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoDiagramType
{
   ExcelConst_msoDiagramMixed = -2,
   ExcelConst_msoDiagramOrgChart = 1,
   ExcelConst_msoDiagramCycle = 2,
   ExcelConst_msoDiagramRadial = 3,
   ExcelConst_msoDiagramPyramid = 4,
   ExcelConst_msoDiagramVenn = 5,
   ExcelConst_msoDiagramTarget = 6,
   _Excel_MsoDiagramTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoAlignCmd
{
   ExcelConst_msoAlignLefts = 0,
   ExcelConst_msoAlignCenters = 1,
   ExcelConst_msoAlignRights = 2,
   ExcelConst_msoAlignTops = 3,
   ExcelConst_msoAlignMiddles = 4,
   ExcelConst_msoAlignBottoms = 5,
   _Excel_MsoAlignCmdForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_MsoDistributeCmd
{
   ExcelConst_msoDistributeHorizontally = 0,
   ExcelConst_msoDistributeVertically = 1,
   _Excel_MsoDistributeCmdForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCalculatedMemberType
{
   ExcelConst_xlCalculatedMember = 0,
   ExcelConst_xlCalculatedSet = 1,
   _Excel_XlCalculatedMemberTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPivotCellType
{
   ExcelConst_xlPivotCellValue = 0,
   ExcelConst_xlPivotCellPivotItem = 1,
   ExcelConst_xlPivotCellSubtotal = 2,
   ExcelConst_xlPivotCellGrandTotal = 3,
   ExcelConst_xlPivotCellDataField = 4,
   ExcelConst_xlPivotCellPivotField = 5,
   ExcelConst_xlPivotCellPageFieldItem = 6,
   ExcelConst_xlPivotCellCustomSubtotal = 7,
   ExcelConst_xlPivotCellDataPivotField = 8,
   ExcelConst_xlPivotCellBlankCell = 9,
   _Excel_XlPivotCellTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSmartTagControlType
{
   ExcelConst_xlSmartTagControlSmartTag = 1,
   ExcelConst_xlSmartTagControlLink = 2,
   ExcelConst_xlSmartTagControlHelp = 3,
   ExcelConst_xlSmartTagControlHelpURL = 4,
   ExcelConst_xlSmartTagControlSeparator = 5,
   ExcelConst_xlSmartTagControlButton = 6,
   ExcelConst_xlSmartTagControlLabel = 7,
   ExcelConst_xlSmartTagControlImage = 8,
   ExcelConst_xlSmartTagControlCheckbox = 9,
   ExcelConst_xlSmartTagControlTextbox = 10,
   ExcelConst_xlSmartTagControlListbox = 11,
   ExcelConst_xlSmartTagControlCombo = 12,
   ExcelConst_xlSmartTagControlActiveX = 13,
   ExcelConst_xlSmartTagControlRadioGroup = 14,
   _Excel_XlSmartTagControlTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSmartTagDisplayMode
{
   ExcelConst_xlIndicatorAndButton = 0,
   ExcelConst_xlDisplayNone = 1,
   ExcelConst_xlButtonOnly = 2,
   _Excel_XlSmartTagDisplayModeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlHebrewModes
{
   ExcelConst_xlHebrewFullScript = 0,
   ExcelConst_xlHebrewPartialScript = 1,
   ExcelConst_xlHebrewMixedScript = 2,
   ExcelConst_xlHebrewMixedAuthorizedScript = 3,
   _Excel_XlHebrewModesForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlArabicModes
{
   ExcelConst_xlArabicNone = 0,
   ExcelConst_xlArabicStrictAlefHamza = 1,
   ExcelConst_xlArabicStrictFinalYaa = 2,
   ExcelConst_xlArabicBothStrict = 3,
   _Excel_XlArabicModesForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSpeakDirection
{
   ExcelConst_xlSpeakByRows = 0,
   ExcelConst_xlSpeakByColumns = 1,
   _Excel_XlSpeakDirectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlListObjectSourceType
{
   ExcelConst_xlSrcExternal = 0,
   ExcelConst_xlSrcRange = 1,
   ExcelConst_xlSrcXml = 2,
   _Excel_XlListObjectSourceTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlListConflict
{
   ExcelConst_xlListConflictDialog = 0,
   ExcelConst_xlListConflictRetryAllConflicts = 1,
   ExcelConst_xlListConflictDiscardAllConflicts = 2,
   ExcelConst_xlListConflictError = 3,
   _Excel_XlListConflictForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTotalsCalculation
{
   ExcelConst_xlTotalsCalculationNone = 0,
   ExcelConst_xlTotalsCalculationSum = 1,
   ExcelConst_xlTotalsCalculationAverage = 2,
   ExcelConst_xlTotalsCalculationCount = 3,
   ExcelConst_xlTotalsCalculationCountNums = 4,
   ExcelConst_xlTotalsCalculationMin = 5,
   ExcelConst_xlTotalsCalculationMax = 6,
   ExcelConst_xlTotalsCalculationStdDev = 7,
   ExcelConst_xlTotalsCalculationVar = 8,
   _Excel_XlTotalsCalculationForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlListDataType
{
   ExcelConst_xlListDataTypeNone = 0,
   ExcelConst_xlListDataTypeText = 1,
   ExcelConst_xlListDataTypeMultiLineText = 2,
   ExcelConst_xlListDataTypeNumber = 3,
   ExcelConst_xlListDataTypeCurrency = 4,
   ExcelConst_xlListDataTypeDateTime = 5,
   ExcelConst_xlListDataTypeChoice = 6,
   ExcelConst_xlListDataTypeChoiceMulti = 7,
   ExcelConst_xlListDataTypeListLookup = 8,
   ExcelConst_xlListDataTypeCheckbox = 9,
   ExcelConst_xlListDataTypeHyperLink = 10,
   ExcelConst_xlListDataTypeCounter = 11,
   ExcelConst_xlListDataTypeMultiLineRichText = 12,
   _Excel_XlListDataTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_Constants
{
   ExcelConst_xlAll = -4104,
   ExcelConst_xlAutomatic = -4105,
   ExcelConst_xlBoth = 1,
   ExcelConst_xlCenter = -4108,
   ExcelConst_xlChecker = 9,
   ExcelConst_xlCircle = 8,
   ExcelConst_xlCorner = 2,
   ExcelConst_xlCrissCross = 16,
   ExcelConst_xlCross = 4,
   ExcelConst_xlDiamond = 2,
   ExcelConst_xlDistributed = -4117,
   ExcelConst_xlDoubleAccounting = 5,
   ExcelConst_xlFixedValue = 1,
   ExcelConst_xlFormats = -4122,
   ExcelConst_xlGray16 = 17,
   ExcelConst_xlGray8 = 18,
   ExcelConst_xlGrid = 15,
   ExcelConst_xlHigh = -4127,
   ExcelConst_xlInside = 2,
   ExcelConst_xlJustify = -4130,
   ExcelConst_xlLightDown = 13,
   ExcelConst_xlLightHorizontal = 11,
   ExcelConst_xlLightUp = 14,
   ExcelConst_xlLightVertical = 12,
   ExcelConst_xlLow = -4134,
   ExcelConst_xlManual = -4135,
   ExcelConst_xlMinusValues = 3,
   ExcelConst_xlModule = -4141,
   ExcelConst_xlNextToAxis = 4,
   ExcelConst_xlNone = -4142,
   ExcelConst_xlNotes = -4144,
   ExcelConst_xlOff = -4146,
   ExcelConst_xlOn = 1,
   ExcelConst_xlPercent = 2,
   ExcelConst_xlPlus = 9,
   ExcelConst_xlPlusValues = 2,
   ExcelConst_xlSemiGray75 = 10,
   ExcelConst_xlShowLabel = 4,
   ExcelConst_xlShowLabelAndPercent = 5,
   ExcelConst_xlShowPercent = 3,
   ExcelConst_xlShowValue = 2,
   ExcelConst_xlSimple = -4154,
   ExcelConst_xlSingle = 2,
   ExcelConst_xlSingleAccounting = 4,
   ExcelConst_xlSolid = 1,
   ExcelConst_xlSquare = 1,
   ExcelConst_xlStar = 5,
   ExcelConst_xlStError = 4,
   ExcelConst_xlToolbarButton = 2,
   ExcelConst_xlTriangle = 3,
   ExcelConst_xlGray25 = -4124,
   ExcelConst_xlGray50 = -4125,
   ExcelConst_xlGray75 = -4126,
   ExcelConst_xlBottom = -4107,
   ExcelConst_xlLeft = -4131,
   ExcelConst_xlRight = -4152,
   ExcelConst_xlTop = -4160,
   ExcelConst_xl3DBar = -4099,
   ExcelConst_xl3DSurface = -4103,
   ExcelConst_xlBar = 2,
   ExcelConst_xlColumn = 3,
   ExcelConst_xlCombination = -4111,
   ExcelConst_xlCustom = -4114,
   ExcelConst_xlDefaultAutoFormat = -1,
   ExcelConst_xlMaximum = 2,
   ExcelConst_xlMinimum = 4,
   ExcelConst_xlOpaque = 3,
   ExcelConst_xlTransparent = 2,
   ExcelConst_xlBidi = -5000,
   ExcelConst_xlLatin = -5001,
   ExcelConst_xlContext = -5002,
   ExcelConst_xlLTR = -5003,
   ExcelConst_xlRTL = -5004,
   ExcelConst_xlFullScript = 1,
   ExcelConst_xlPartialScript = 2,
   ExcelConst_xlMixedScript = 3,
   ExcelConst_xlMixedAuthorizedScript = 4,
   ExcelConst_xlVisualCursor = 2,
   ExcelConst_xlLogicalCursor = 1,
   ExcelConst_xlSystem = 1,
   ExcelConst_xlPartial = 3,
   ExcelConst_xlHindiNumerals = 3,
   ExcelConst_xlBidiCalendar = 3,
   ExcelConst_xlGregorian = 2,
   ExcelConst_xlComplete = 4,
   ExcelConst_xlScale = 3,
   ExcelConst_xlClosed = 3,
   ExcelConst_xlColor1 = 7,
   ExcelConst_xlColor2 = 8,
   ExcelConst_xlColor3 = 9,
   ExcelConst_xlConstants = 2,
   ExcelConst_xlContents = 2,
   ExcelConst_xlBelow = 1,
   ExcelConst_xlCascade = 7,
   ExcelConst_xlCenterAcrossSelection = 7,
   ExcelConst_xlChart4 = 2,
   ExcelConst_xlChartSeries = 17,
   ExcelConst_xlChartShort = 6,
   ExcelConst_xlChartTitles = 18,
   ExcelConst_xlClassic1 = 1,
   ExcelConst_xlClassic2 = 2,
   ExcelConst_xlClassic3 = 3,
   ExcelConst_xl3DEffects1 = 13,
   ExcelConst_xl3DEffects2 = 14,
   ExcelConst_xlAbove = 0,
   ExcelConst_xlAccounting1 = 4,
   ExcelConst_xlAccounting2 = 5,
   ExcelConst_xlAccounting3 = 6,
   ExcelConst_xlAccounting4 = 17,
   ExcelConst_xlAdd = 2,
   ExcelConst_xlDebugCodePane = 13,
   ExcelConst_xlDesktop = 9,
   ExcelConst_xlDirect = 1,
   ExcelConst_xlDivide = 5,
   ExcelConst_xlDoubleClosed = 5,
   ExcelConst_xlDoubleOpen = 4,
   ExcelConst_xlDoubleQuote = 1,
   ExcelConst_xlEntireChart = 20,
   ExcelConst_xlExcelMenus = 1,
   ExcelConst_xlExtended = 3,
   ExcelConst_xlFill = 5,
   ExcelConst_xlFirst = 0,
   ExcelConst_xlFloating = 5,
   ExcelConst_xlFormula = 5,
   ExcelConst_xlGeneral = 1,
   ExcelConst_xlGridline = 22,
   ExcelConst_xlIcons = 1,
   ExcelConst_xlImmediatePane = 12,
   ExcelConst_xlInteger = 2,
   ExcelConst_xlLast = 1,
   ExcelConst_xlLastCell = 11,
   ExcelConst_xlList1 = 10,
   ExcelConst_xlList2 = 11,
   ExcelConst_xlList3 = 12,
   ExcelConst_xlLocalFormat1 = 15,
   ExcelConst_xlLocalFormat2 = 16,
   ExcelConst_xlLong = 3,
   ExcelConst_xlLotusHelp = 2,
   ExcelConst_xlMacrosheetCell = 7,
   ExcelConst_xlMixed = 2,
   ExcelConst_xlMultiply = 4,
   ExcelConst_xlNarrow = 1,
   ExcelConst_xlNoDocuments = 3,
   ExcelConst_xlOpen = 2,
   ExcelConst_xlOutside = 3,
   ExcelConst_xlReference = 4,
   ExcelConst_xlSemiautomatic = 2,
   ExcelConst_xlShort = 1,
   ExcelConst_xlSingleQuote = 2,
   ExcelConst_xlStrict = 2,
   ExcelConst_xlSubtract = 3,
   ExcelConst_xlTextBox = 16,
   ExcelConst_xlTiled = 1,
   ExcelConst_xlTitleBar = 8,
   ExcelConst_xlToolbar = 1,
   ExcelConst_xlVisible = 12,
   ExcelConst_xlWatchPane = 11,
   ExcelConst_xlWide = 3,
   ExcelConst_xlWorkbookTab = 6,
   ExcelConst_xlWorksheet4 = 1,
   ExcelConst_xlWorksheetCell = 3,
   ExcelConst_xlWorksheetShort = 5,
   ExcelConst_xlAllExceptBorders = 7,
   ExcelConst_xlLeftToRight = 2,
   ExcelConst_xlTopToBottom = 1,
   ExcelConst_xlVeryHidden = 2,
   ExcelConst_xlDrawingObject = 14,
   _Excel_ConstantsForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlChartGallery
{
   ExcelConst_xlBuiltIn = 21,
   ExcelConst_xlUserDefined = 22,
   ExcelConst_xlAnyGallery = 23,
   _Excel_XlChartGalleryForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlBackground
{
   ExcelConst_xlBackgroundAutomatic = -4105,
   ExcelConst_xlBackgroundOpaque = 3,
   ExcelConst_xlBackgroundTransparent = 2,
   _Excel_XlBackgroundForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlArrowHeadLength
{
   ExcelConst_xlArrowHeadLengthLong = 3,
   ExcelConst_xlArrowHeadLengthMedium = -4138,
   ExcelConst_xlArrowHeadLengthShort = 1,
   _Excel_XlArrowHeadLengthForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlArrowHeadStyle
{
   ExcelConst_xlArrowHeadStyleClosed = 3,
   ExcelConst_xlArrowHeadStyleDoubleClosed = 5,
   ExcelConst_xlArrowHeadStyleDoubleOpen = 4,
   ExcelConst_xlArrowHeadStyleNone = -4142,
   ExcelConst_xlArrowHeadStyleOpen = 2,
   _Excel_XlArrowHeadStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlArrowHeadWidth
{
   ExcelConst_xlArrowHeadWidthMedium = -4138,
   ExcelConst_xlArrowHeadWidthNarrow = 1,
   ExcelConst_xlArrowHeadWidthWide = 3,
   _Excel_XlArrowHeadWidthForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlChartPicturePlacement
{
   ExcelConst_xlSides = 1,
   ExcelConst_xlEnd = 2,
   ExcelConst_xlEndSides = 3,
   ExcelConst_xlFront = 4,
   ExcelConst_xlFrontSides = 5,
   ExcelConst_xlFrontEnd = 6,
   ExcelConst_xlAllFaces = 7,
   _Excel_XlChartPicturePlacementForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlUnderlineStyle
{
   ExcelConst_xlUnderlineStyleDouble = -4119,
   ExcelConst_xlUnderlineStyleDoubleAccounting = 5,
   ExcelConst_xlUnderlineStyleNone = -4142,
   ExcelConst_xlUnderlineStyleSingle = 2,
   ExcelConst_xlUnderlineStyleSingleAccounting = 4,
   _Excel_XlUnderlineStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLineStyle
{
   ExcelConst_xlContinuous = 1,
   ExcelConst_xlDash = -4115,
   ExcelConst_xlDashDot = 4,
   ExcelConst_xlDashDotDot = 5,
   ExcelConst_xlDot = -4118,
   ExcelConst_xlDouble = -4119,
   ExcelConst_xlSlantDashDot = 13,
   ExcelConst_xlLineStyleNone = -4142,
   _Excel_XlLineStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPictureConvertorType
{
   ExcelConst_xlBMP = 1,
   ExcelConst_xlCGM = 7,
   ExcelConst_xlDRW = 4,
   ExcelConst_xlDXF = 5,
   ExcelConst_xlEPS = 8,
   ExcelConst_xlHGL = 6,
   ExcelConst_xlPCT = 13,
   ExcelConst_xlPCX = 10,
   ExcelConst_xlPIC = 11,
   ExcelConst_xlPLT = 12,
   ExcelConst_xlTIF = 9,
   ExcelConst_xlWMF = 2,
   ExcelConst_xlWPG = 3,
   _Excel_XlPictureConvertorTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPattern
{
   ExcelConst_xlPatternAutomatic = -4105,
   ExcelConst_xlPatternChecker = 9,
   ExcelConst_xlPatternCrissCross = 16,
   ExcelConst_xlPatternDown = -4121,
   ExcelConst_xlPatternGray16 = 17,
   ExcelConst_xlPatternGray25 = -4124,
   ExcelConst_xlPatternGray50 = -4125,
   ExcelConst_xlPatternGray75 = -4126,
   ExcelConst_xlPatternGray8 = 18,
   ExcelConst_xlPatternGrid = 15,
   ExcelConst_xlPatternHorizontal = -4128,
   ExcelConst_xlPatternLightDown = 13,
   ExcelConst_xlPatternLightHorizontal = 11,
   ExcelConst_xlPatternLightUp = 14,
   ExcelConst_xlPatternLightVertical = 12,
   ExcelConst_xlPatternNone = -4142,
   ExcelConst_xlPatternSemiGray75 = 10,
   ExcelConst_xlPatternSolid = 1,
   ExcelConst_xlPatternUp = -4162,
   ExcelConst_xlPatternVertical = -4166,
   _Excel_XlPatternForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlChartItem
{
   ExcelConst_xlDataLabel = 0,
   ExcelConst_xlChartArea = 2,
   ExcelConst_xlSeries = 3,
   ExcelConst_xlChartTitle = 4,
   ExcelConst_xlWalls = 5,
   ExcelConst_xlCorners = 6,
   ExcelConst_xlDataTable = 7,
   ExcelConst_xlTrendline = 8,
   ExcelConst_xlErrorBars = 9,
   ExcelConst_xlXErrorBars = 10,
   ExcelConst_xlYErrorBars = 11,
   ExcelConst_xlLegendEntry = 12,
   ExcelConst_xlLegendKey = 13,
   ExcelConst_xlShape = 14,
   ExcelConst_xlMajorGridlines = 15,
   ExcelConst_xlMinorGridlines = 16,
   ExcelConst_xlAxisTitle = 17,
   ExcelConst_xlUpBars = 18,
   ExcelConst_xlPlotArea = 19,
   ExcelConst_xlDownBars = 20,
   ExcelConst_xlAxis = 21,
   ExcelConst_xlSeriesLines = 22,
   ExcelConst_xlFloor = 23,
   ExcelConst_xlLegend = 24,
   ExcelConst_xlHiLoLines = 25,
   ExcelConst_xlDropLines = 26,
   ExcelConst_xlRadarAxisLabels = 27,
   ExcelConst_xlNothing = 28,
   ExcelConst_xlLeaderLines = 29,
   ExcelConst_xlDisplayUnitLabel = 30,
   ExcelConst_xlPivotChartFieldButton = 31,
   ExcelConst_xlPivotChartDropZone = 32,
   _Excel_XlChartItemForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlInsertShiftDirection
{
   ExcelConst_xlShiftDown = -4121,
   ExcelConst_xlShiftToRight = -4161,
   _Excel_XlInsertShiftDirectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDeleteShiftDirection
{
   ExcelConst_xlShiftToLeft = -4159,
   ExcelConst_xlShiftUp = -4162,
   _Excel_XlDeleteShiftDirectionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFindLookIn
{
   ExcelConst_xlFormulas = -4123,
   ExcelConst_xlComments = -4144,
   ExcelConst_xlValues = -4163,
   _Excel_XlFindLookInForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlMouseButton
{
   ExcelConst_xlNoButton = 0,
   ExcelConst_xlPrimaryButton = 1,
   ExcelConst_xlSecondaryButton = 2,
   _Excel_XlMouseButtonForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlOLEType
{
   ExcelConst_xlOLEControl = 2,
   ExcelConst_xlOLEEmbed = 1,
   ExcelConst_xlOLELink = 0,
   _Excel_XlOLETypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLookAt
{
   ExcelConst_xlPart = 2,
   ExcelConst_xlWhole = 1,
   _Excel_XlLookAtForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLinkInfoType
{
   ExcelConst_xlLinkInfoOLELinks = 2,
   ExcelConst_xlLinkInfoPublishers = 5,
   ExcelConst_xlLinkInfoSubscribers = 6,
   _Excel_XlLinkInfoTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCVError
{
   ExcelConst_xlErrDiv0 = 2007,
   ExcelConst_xlErrNA = 2042,
   ExcelConst_xlErrName = 2029,
   ExcelConst_xlErrNull = 2000,
   ExcelConst_xlErrNum = 2036,
   ExcelConst_xlErrRef = 2023,
   ExcelConst_xlErrValue = 2015,
   _Excel_XlCVErrorForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlEditionFormat
{
   ExcelConst_xlBIFF = 2,
   ExcelConst_xlPICT = 1,
   ExcelConst_xlRTF = 4,
   ExcelConst_xlVALU = 8,
   _Excel_XlEditionFormatForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLink
{
   ExcelConst_xlExcelLinks = 1,
   ExcelConst_xlOLELinks = 2,
   ExcelConst_xlPublishers = 5,
   ExcelConst_xlSubscribers = 6,
   _Excel_XlLinkForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlClipboardFormat
{
   ExcelConst_xlClipboardFormatBIFF = 8,
   ExcelConst_xlClipboardFormatBIFF2 = 18,
   ExcelConst_xlClipboardFormatBIFF3 = 20,
   ExcelConst_xlClipboardFormatBIFF4 = 30,
   ExcelConst_xlClipboardFormatBinary = 15,
   ExcelConst_xlClipboardFormatBitmap = 9,
   ExcelConst_xlClipboardFormatCGM = 13,
   ExcelConst_xlClipboardFormatCSV = 5,
   ExcelConst_xlClipboardFormatDIF = 4,
   ExcelConst_xlClipboardFormatDspText = 12,
   ExcelConst_xlClipboardFormatEmbeddedObject = 21,
   ExcelConst_xlClipboardFormatEmbedSource = 22,
   ExcelConst_xlClipboardFormatLink = 11,
   ExcelConst_xlClipboardFormatLinkSource = 23,
   ExcelConst_xlClipboardFormatLinkSourceDesc = 32,
   ExcelConst_xlClipboardFormatMovie = 24,
   ExcelConst_xlClipboardFormatNative = 14,
   ExcelConst_xlClipboardFormatObjectDesc = 31,
   ExcelConst_xlClipboardFormatObjectLink = 19,
   ExcelConst_xlClipboardFormatOwnerLink = 17,
   ExcelConst_xlClipboardFormatPICT = 2,
   ExcelConst_xlClipboardFormatPrintPICT = 3,
   ExcelConst_xlClipboardFormatRTF = 7,
   ExcelConst_xlClipboardFormatScreenPICT = 29,
   ExcelConst_xlClipboardFormatStandardFont = 28,
   ExcelConst_xlClipboardFormatStandardScale = 27,
   ExcelConst_xlClipboardFormatSYLK = 6,
   ExcelConst_xlClipboardFormatTable = 16,
   ExcelConst_xlClipboardFormatText = 0,
   ExcelConst_xlClipboardFormatToolFace = 25,
   ExcelConst_xlClipboardFormatToolFacePICT = 26,
   ExcelConst_xlClipboardFormatVALU = 1,
   ExcelConst_xlClipboardFormatWK1 = 10,
   _Excel_XlClipboardFormatForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlApplicationInternational
{
   ExcelConst_xl24HourClock = 33,
   ExcelConst_xl4DigitYears = 43,
   ExcelConst_xlAlternateArraySeparator = 16,
   ExcelConst_xlColumnSeparator = 14,
   ExcelConst_xlCountryCode = 1,
   ExcelConst_xlCountrySetting = 2,
   ExcelConst_xlCurrencyBefore = 37,
   ExcelConst_xlCurrencyCode = 25,
   ExcelConst_xlCurrencyDigits = 27,
   ExcelConst_xlCurrencyLeadingZeros = 40,
   ExcelConst_xlCurrencyMinusSign = 38,
   ExcelConst_xlCurrencyNegative = 28,
   ExcelConst_xlCurrencySpaceBefore = 36,
   ExcelConst_xlCurrencyTrailingZeros = 39,
   ExcelConst_xlDateOrder = 32,
   ExcelConst_xlDateSeparator = 17,
   ExcelConst_xlDayCode = 21,
   ExcelConst_xlDayLeadingZero = 42,
   ExcelConst_xlDecimalSeparator = 3,
   ExcelConst_xlGeneralFormatName = 26,
   ExcelConst_xlHourCode = 22,
   ExcelConst_xlLeftBrace = 12,
   ExcelConst_xlLeftBracket = 10,
   ExcelConst_xlListSeparator = 5,
   ExcelConst_xlLowerCaseColumnLetter = 9,
   ExcelConst_xlLowerCaseRowLetter = 8,
   ExcelConst_xlMDY = 44,
   ExcelConst_xlMetric = 35,
   ExcelConst_xlMinuteCode = 23,
   ExcelConst_xlMonthCode = 20,
   ExcelConst_xlMonthLeadingZero = 41,
   ExcelConst_xlMonthNameChars = 30,
   ExcelConst_xlNoncurrencyDigits = 29,
   ExcelConst_xlNonEnglishFunctions = 34,
   ExcelConst_xlRightBrace = 13,
   ExcelConst_xlRightBracket = 11,
   ExcelConst_xlRowSeparator = 15,
   ExcelConst_xlSecondCode = 24,
   ExcelConst_xlThousandsSeparator = 4,
   ExcelConst_xlTimeLeadingZero = 45,
   ExcelConst_xlTimeSeparator = 18,
   ExcelConst_xlUpperCaseColumnLetter = 7,
   ExcelConst_xlUpperCaseRowLetter = 6,
   ExcelConst_xlWeekdayNameChars = 31,
   ExcelConst_xlYearCode = 19,
   _Excel_XlApplicationInternationalForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlHighlightChangesTime
{
   ExcelConst_xlSinceMyLastSave = 1,
   ExcelConst_xlAllChanges = 2,
   ExcelConst_xlNotYetReviewed = 3,
   _Excel_XlHighlightChangesTimeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlFormatConditionOperator
{
   ExcelConst_xlBetween = 1,
   ExcelConst_xlNotBetween = 2,
   ExcelConst_xlEqual = 3,
   ExcelConst_xlNotEqual = 4,
   ExcelConst_xlGreater = 5,
   ExcelConst_xlLess = 6,
   ExcelConst_xlGreaterEqual = 7,
   ExcelConst_xlLessEqual = 8,
   _Excel_XlFormatConditionOperatorForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlIMEMode
{
   ExcelConst_xlIMEModeNoControl = 0,
   ExcelConst_xlIMEModeOn = 1,
   ExcelConst_xlIMEModeOff = 2,
   ExcelConst_xlIMEModeDisable = 3,
   ExcelConst_xlIMEModeHiragana = 4,
   ExcelConst_xlIMEModeKatakana = 5,
   ExcelConst_xlIMEModeKatakanaHalf = 6,
   ExcelConst_xlIMEModeAlphaFull = 7,
   ExcelConst_xlIMEModeAlpha = 8,
   ExcelConst_xlIMEModeHangulFull = 9,
   ExcelConst_xlIMEModeHangul = 10,
   _Excel_XlIMEModeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDVAlertStyle
{
   ExcelConst_xlValidAlertStop = 1,
   ExcelConst_xlValidAlertWarning = 2,
   ExcelConst_xlValidAlertInformation = 3,
   _Excel_XlDVAlertStyleForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPhoneticCharacterType
{
   ExcelConst_xlKatakanaHalf = 0,
   ExcelConst_xlKatakana = 1,
   ExcelConst_xlHiragana = 2,
   ExcelConst_xlNoConversion = 3,
   _Excel_XlPhoneticCharacterTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPhoneticAlignment
{
   ExcelConst_xlPhoneticAlignNoControl = 0,
   ExcelConst_xlPhoneticAlignLeft = 1,
   ExcelConst_xlPhoneticAlignCenter = 2,
   ExcelConst_xlPhoneticAlignDistributed = 3,
   _Excel_XlPhoneticAlignmentForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlPlatform
{
   ExcelConst_xlMacintosh = 1,
   ExcelConst_xlMSDOS = 3,
   ExcelConst_xlWindows = 2,
   _Excel_XlPlatformForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlReferenceType
{
   ExcelConst_xlAbsolute = 1,
   ExcelConst_xlAbsRowRelColumn = 2,
   ExcelConst_xlRelative = 4,
   ExcelConst_xlRelRowAbsColumn = 3,
   _Excel_XlReferenceTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSaveAction
{
   ExcelConst_xlDoNotSaveChanges = 2,
   ExcelConst_xlSaveChanges = 1,
   _Excel_XlSaveActionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSearchOrder
{
   ExcelConst_xlByColumns = 2,
   ExcelConst_xlByRows = 1,
   _Excel_XlSearchOrderForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSortMethodOld
{
   ExcelConst_xlCodePage = 2,
   ExcelConst_xlSyllabary = 1,
   _Excel_XlSortMethodOldForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSortType
{
   ExcelConst_xlSortLabels = 2,
   ExcelConst_xlSortValues = 1,
   _Excel_XlSortTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSpecialCellsValue
{
   ExcelConst_xlErrors = 16,
   ExcelConst_xlLogical = 4,
   ExcelConst_xlNumbers = 1,
   ExcelConst_xlTextValues = 2,
   _Excel_XlSpecialCellsValueForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlTabPosition
{
   ExcelConst_xlTabPositionFirst = 0,
   ExcelConst_xlTabPositionLast = 1,
   _Excel_XlTabPositionForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlWBATemplate
{
   ExcelConst_xlWBATChart = -4109,
   ExcelConst_xlWBATExcel4IntlMacroSheet = 4,
   ExcelConst_xlWBATExcel4MacroSheet = 3,
   ExcelConst_xlWBATWorksheet = -4167,
   _Excel_XlWBATemplateForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlColumnDataType
{
   ExcelConst_xlGeneralFormat = 1,
   ExcelConst_xlTextFormat = 2,
   ExcelConst_xlMDYFormat = 3,
   ExcelConst_xlDMYFormat = 4,
   ExcelConst_xlYMDFormat = 5,
   ExcelConst_xlMYDFormat = 6,
   ExcelConst_xlDYMFormat = 7,
   ExcelConst_xlYDMFormat = 8,
   ExcelConst_xlSkipColumn = 9,
   ExcelConst_xlEMDFormat = 10,
   _Excel_XlColumnDataTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlLinkStatus
{
   ExcelConst_xlLinkStatusOK = 0,
   ExcelConst_xlLinkStatusMissingFile = 1,
   ExcelConst_xlLinkStatusMissingSheet = 2,
   ExcelConst_xlLinkStatusOld = 3,
   ExcelConst_xlLinkStatusSourceNotCalculated = 4,
   ExcelConst_xlLinkStatusIndeterminate = 5,
   ExcelConst_xlLinkStatusNotStarted = 6,
   ExcelConst_xlLinkStatusInvalidName = 7,
   ExcelConst_xlLinkStatusSourceNotOpen = 8,
   ExcelConst_xlLinkStatusSourceOpen = 9,
   ExcelConst_xlLinkStatusCopiedValues = 10,
   _Excel_XlLinkStatusForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlSearchWithin
{
   ExcelConst_xlWithinSheet = 1,
   ExcelConst_xlWithinWorkbook = 2,
   _Excel_XlSearchWithinForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlCorruptLoad
{
   ExcelConst_xlNormalLoad = 0,
   ExcelConst_xlRepairFile = 1,
   ExcelConst_xlExtractData = 2,
   _Excel_XlCorruptLoadForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlErrorChecks
{
   ExcelConst_xlEvaluateToError = 1,
   ExcelConst_xlTextDate = 2,
   ExcelConst_xlNumberAsText = 3,
   ExcelConst_xlInconsistentFormula = 4,
   ExcelConst_xlOmittedCells = 5,
   ExcelConst_xlUnlockedFormulaCells = 6,
   ExcelConst_xlEmptyCellReferences = 7,
   ExcelConst_xlListDataValidation = 8,
   _Excel_XlErrorChecksForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlDataLabelSeparator
{
   ExcelConst_xlDataLabelSeparatorDefault = 1,
   _Excel_XlDataLabelSeparatorForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlRangeValueDataType
{
   ExcelConst_xlRangeValueDefault = 10,
   ExcelConst_xlRangeValueXMLSpreadsheet = 11,
   ExcelConst_xlRangeValueMSPersistXML = 12,
   _Excel_XlRangeValueDataTypeForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlInsertFormatOrigin
{
   ExcelConst_xlFormatFromLeftOrAbove = 0,
   ExcelConst_xlFormatFromRightOrBelow = 1,
   _Excel_XlInsertFormatOriginForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlImportDataAs
{
   ExcelConst_xlQueryTable = 0,
   ExcelConst_xlPivotTableReport = 1,
   _Excel_XlImportDataAsForceSizeToFourBytes = 0xFFFFFFFF
};
enum ExcelEnum_XlXmlLoadOption
{
   ExcelConst_xlXmlLoadPromptUser = 0,
   ExcelConst_xlXmlLoadOpenXml = 1,
   ExcelConst_xlXmlLoadImportToList = 2,
   ExcelConst_xlXmlLoadMapXml = 3,
   _Excel_XlXmlLoadOptionForceSizeToFourBytes = 0xFFFFFFFF
};
typedef CAObjHandle ExcelObj_App;
typedef CAObjHandle ExcelObj_Range;
typedef CAObjHandle ExcelObj_Parameters;
typedef CAObjHandle ExcelObj_ListObject;
typedef CAObjHandle ExcelObj_Chart;
typedef CAObjHandle ExcelObj_DialogSheet;
typedef CAObjHandle ExcelObj_MenuBar;
typedef CAObjHandle ExcelObj_Window;
typedef CAObjHandle ExcelObj_Workbook;
typedef CAObjHandle ExcelObj_AddIns;
typedef CAObjHandle ExcelObj_Assistant;
typedef CAObjHandle ExcelObj_Sheets;
typedef CAObjHandle ExcelObj__CommandBars;
typedef CAObjHandle ExcelObj_MenuBars;
typedef CAObjHandle ExcelObj_Modules;
typedef CAObjHandle ExcelObj_Names;
typedef CAObjHandle ExcelObj_Menu;
typedef CAObjHandle ExcelObj_Toolbars;
typedef CAObjHandle ExcelObj_Windows;
typedef CAObjHandle ExcelObj_Workbooks;
typedef CAObjHandle ExcelObj_WorksheetFunction;
typedef CAObjHandle ExcelObj_AutoCorrect;
typedef CAObjHandle ExcelObj_Dialogs;
typedef CAObjHandle ExcelObj_FileSearch;
typedef CAObjHandle ExcelObj_IFind;
typedef CAObjHandle ExcelObj_RecentFiles;
typedef CAObjHandle ExcelObj_ODBCErrors;
typedef CAObjHandle ExcelObj_VBE;
typedef CAObjHandle ExcelObj_OLEDBErrors;
typedef CAObjHandle ExcelObj_COMAddIns;
typedef CAObjHandle ExcelObj_DefaultWebOptions;
typedef CAObjHandle ExcelObj_LanguageSettings;
typedef CAObjHandle ExcelObj_PivotTable;
typedef CAObjHandle ExcelObj_AnswerWizard;
typedef CAObjHandle ExcelObj_CellFormat;
typedef CAObjHandle ExcelObj_UsedObjects;
typedef CAObjHandle ExcelObj_Watches;
typedef CAObjHandle ExcelObj_FileDialog;
typedef CAObjHandle ExcelObj_AutoRecover;
typedef CAObjHandle ExcelObj_ErrorCheckingOptions;
typedef CAObjHandle ExcelObj_SmartTagRecognizers;
typedef CAObjHandle ExcelObj_NewFile;
typedef CAObjHandle ExcelObj_SpellingOptions;
typedef CAObjHandle ExcelObj_Speech;
typedef CAObjHandle ExcelObj_RTD;
typedef CAObjHandle ExcelObj_Hyperlink;
typedef CAObjHandle ExcelObj_XmlMap;
typedef CAObjHandle ExcelObj_PageSetup;
typedef CAObjHandle ExcelObj_Shapes;
typedef CAObjHandle ExcelObj_ChartGroup;
typedef CAObjHandle ExcelObj_ChartArea;
typedef CAObjHandle ExcelObj_ChartTitle;
typedef CAObjHandle ExcelObj_Corners;
typedef CAObjHandle ExcelObj_DataTable;
typedef CAObjHandle ExcelObj_Floor;
typedef CAObjHandle ExcelObj_Hyperlinks;
typedef CAObjHandle ExcelObj_Legend;
typedef CAObjHandle ExcelObj_PlotArea;
typedef CAObjHandle ExcelObj_Walls;
typedef CAObjHandle ExcelObj_PivotLayout;
typedef CAObjHandle ExcelObj_Scripts;
typedef CAObjHandle ExcelObj_Tab;
typedef CAObjHandle ExcelObj_IMsoEnvelopeVB;
typedef CAObjHandle ExcelObj_Outline;
typedef CAObjHandle ExcelObj_HPageBreaks;
typedef CAObjHandle ExcelObj_VPageBreaks;
typedef CAObjHandle ExcelObj_QueryTables;
typedef CAObjHandle ExcelObj_Comments;
typedef CAObjHandle ExcelObj_AutoFilter;
typedef CAObjHandle ExcelObj_CustomProperties;
typedef CAObjHandle ExcelObj_SmartTags;
typedef CAObjHandle ExcelObj_Protection;
typedef CAObjHandle ExcelObj_ListObjects;
typedef CAObjHandle ExcelObj_Mailer;
typedef CAObjHandle ExcelObj_PivotCaches;
typedef CAObjHandle ExcelObj_RoutingSlip;
typedef CAObjHandle ExcelObj_Styles;
typedef CAObjHandle ExcelObj_CustomViews;
typedef CAObjHandle ExcelObj__VBProject;
typedef CAObjHandle ExcelObj_PublishObjects;
typedef CAObjHandle ExcelObj_WebOptions;
typedef CAObjHandle ExcelObj_HTMLProject;
typedef CAObjHandle ExcelObj_SmartTagOptions;
typedef CAObjHandle ExcelObj_Permission;
typedef CAObjHandle ExcelObj_SharedWorkspace;
typedef CAObjHandle ExcelObj_Sync;
typedef CAObjHandle ExcelObj_XmlNamespaces;
typedef CAObjHandle ExcelObj_XmlMaps;
typedef CAObjHandle ExcelObj_SmartDocument;
typedef CAObjHandle ExcelObj_DocumentLibraryVersions;
typedef CAObjHandle ExcelObj_ShapeRange;
typedef CAObjHandle ExcelObj_Border;
typedef CAObjHandle ExcelObj_Interior;
typedef long ExcelType_MsoRGBType;
typedef CAObjHandle ExcelObj_ColorFormat;
typedef CAObjHandle ExcelObj_ShapeNode;
typedef CAObjHandle ExcelObj_DiagramNode;
typedef CAObjHandle ExcelObj_DiagramNodeChildren;
typedef CAObjHandle ExcelObj_Shape;
typedef CAObjHandle ExcelObj_IMsoDiagram;
typedef CAObjHandle ExcelObj_IRTDUpdateEvent;
typedef CAObjHandle ExcelObj_WebPageFonts;
typedef CAObjHandle ExcelObj_TreeviewControl;
typedef CAObjHandle ExcelObj_PivotFields;
typedef CAObjHandle ExcelObj_CubeField;
typedef CAObjHandle ExcelObj_Pane;
typedef CAObjHandle ExcelObj_Panes;
typedef CAObjHandle ExcelObj_Areas;
typedef CAObjHandle ExcelObj_Borders;
typedef CAObjHandle ExcelObj_Characters;
typedef CAObjHandle ExcelObj_Font;
typedef CAObjHandle ExcelObj_PivotField;
typedef CAObjHandle ExcelObj_PivotItem;
typedef CAObjHandle ExcelObj_QueryTable;
typedef CAObjHandle ExcelObj_SoundNote;
typedef CAObjHandle ExcelObj_Validation;
typedef CAObjHandle ExcelObj_Worksheet;
typedef CAObjHandle ExcelObj_Comment;
typedef CAObjHandle ExcelObj_Phonetic;
typedef CAObjHandle ExcelObj_FormatConditions;
typedef CAObjHandle ExcelObj_Phonetics;
typedef CAObjHandle ExcelObj_PivotCell;
typedef CAObjHandle ExcelObj_Errors;
typedef CAObjHandle ExcelObj_XPath;
typedef CAObjHandle ExcelObj_HPageBreak;
typedef CAObjHandle ExcelObj_VPageBreak;
typedef CAObjHandle ExcelObj_RecentFile;
typedef CAObjHandle ExcelObj_Style;
typedef CAObjHandle ExcelObj_AddIn;
typedef CAObjHandle ExcelObj_ToolbarButtons;
typedef CAObjHandle ExcelObj_Toolbar;
typedef CAObjHandle ExcelObj_ToolbarButton;
typedef CAObjHandle ExcelObj_Menus;
typedef CAObjHandle ExcelObj_MenuItems;
typedef CAObjHandle ExcelObj_MenuItem;
typedef CAObjHandle ExcelObj_GroupObject;
typedef CAObjHandle ExcelObj_PivotCache;
typedef CAObjHandle ExcelObj_PivotFormula;
typedef CAObjHandle ExcelObj_CalculatedFields;
typedef CAObjHandle ExcelObj_PivotFormulas;
typedef CAObjHandle ExcelObj_CubeFields;
typedef CAObjHandle ExcelObj_CalculatedMembers;
typedef CAObjHandle ExcelObj_CalculatedItems;
typedef CAObjHandle ExcelObj_Dialog;
typedef CAObjHandle ExcelObj_Button;
typedef CAObjHandle ExcelObj_CheckBox;
typedef CAObjHandle ExcelObj_GroupBox;
typedef CAObjHandle ExcelObj_OptionButton;
typedef CAObjHandle ExcelObj_EditBox;
typedef CAObjHandle ExcelObj_ScrollBar;
typedef CAObjHandle ExcelObj_ListBox;
typedef CAObjHandle ExcelObj_DropDown;
typedef CAObjHandle ExcelObj_Spinner;
typedef CAObjHandle ExcelObj_Label;
typedef CAObjHandle ExcelObj_Scenario;
typedef CAObjHandle ExcelObj_Line;
typedef CAObjHandle ExcelObj_Rectangle;
typedef CAObjHandle ExcelObj_Oval;
typedef CAObjHandle ExcelObj_Arc;
typedef CAObjHandle ExcelObj_OLEObject;
typedef CAObjHandle ExcelObj_TextBox;
typedef CAObjHandle ExcelObj_Picture;
typedef CAObjHandle ExcelObj_Drawing;
typedef CAObjHandle ExcelObj_Module;
typedef CAObjHandle ExcelObj_DialogFrame;
typedef CAObjHandle ExcelObj_Graphic;
typedef CAObjHandle ExcelObj_Name;
typedef CAObjHandle ExcelObj_ChartObject;
typedef CAObjHandle ExcelObj_CustomView;
typedef CAObjHandle ExcelObj_FormatCondition;
typedef CAObjHandle ExcelObj_Parameter;
typedef CAObjHandle ExcelObj_ODBCError;
typedef CAObjHandle ExcelObj_Filters;
typedef CAObjHandle ExcelObj_Filter;
typedef CAObjHandle ExcelObj_ChartColorFormat;
typedef CAObjHandle ExcelObj_AxisTitle;
typedef CAObjHandle ExcelObj_Gridlines;
typedef CAObjHandle ExcelObj_TickLabels;
typedef CAObjHandle ExcelObj_DisplayUnitLabel;
typedef CAObjHandle ExcelObj_ChartFillFormat;
typedef CAObjHandle ExcelObj_DownBars;
typedef CAObjHandle ExcelObj_DropLines;
typedef CAObjHandle ExcelObj_HiLoLines;
typedef CAObjHandle ExcelObj_SeriesLines;
typedef CAObjHandle ExcelObj_UpBars;
typedef CAObjHandle ExcelObj_Axis;
typedef CAObjHandle ExcelObj_Point;
typedef CAObjHandle ExcelObj_DataLabel;
typedef CAObjHandle ExcelObj_ErrorBars;
typedef CAObjHandle ExcelObj_LeaderLines;
typedef CAObjHandle ExcelObj_Series;
typedef CAObjHandle ExcelObj_LegendKey;
typedef CAObjHandle ExcelObj_LegendEntry;
typedef CAObjHandle ExcelObj_Trendline;
typedef CAObjHandle ExcelObj_Adjustments;
typedef CAObjHandle ExcelObj_TextFrame;
typedef CAObjHandle ExcelObj_CalloutFormat;
typedef CAObjHandle ExcelObj_ConnectorFormat;
typedef CAObjHandle ExcelObj_FillFormat;
typedef CAObjHandle ExcelObj_GroupShapes;
typedef CAObjHandle ExcelObj_LineFormat;
typedef CAObjHandle ExcelObj_ShapeNodes;
typedef CAObjHandle ExcelObj_PictureFmt;
typedef CAObjHandle ExcelObj_ShadowFormat;
typedef CAObjHandle ExcelObj_TextEffectFmt;
typedef CAObjHandle ExcelObj_ThreeDFmt;
typedef CAObjHandle ExcelObj_ControlFormat;
typedef CAObjHandle ExcelObj_LinkFormat;
typedef CAObjHandle ExcelObj_OLEFormat;
typedef CAObjHandle ExcelObj_Script;
typedef CAObjHandle ExcelObj_Diagram;
typedef CAObjHandle ExcelObj_CanvasShapes;
typedef CAObjHandle ExcelObj_FreeformBuilder;
typedef CAObjHandle ExcelObj_PublishObject;
typedef CAObjHandle ExcelObj_OLEDBError;
typedef CAObjHandle ExcelObj_CustomProperty;
typedef CAObjHandle ExcelObj_CalculatedMember;
typedef CAObjHandle ExcelObj_Watch;
typedef CAObjHandle ExcelObj_PivotItemList;
typedef CAObjHandle ExcelObj_Error;
typedef CAObjHandle ExcelObj_SmartTagAction;
typedef CAObjHandle ExcelObj_SmartTagActions;
typedef CAObjHandle ExcelObj_SmartTag;
typedef CAObjHandle ExcelObj_SmartTagRecognizer;
typedef CAObjHandle ExcelObj_AllowEditRanges;
typedef CAObjHandle ExcelObj_AllowEditRange;
typedef CAObjHandle ExcelObj_UserAccessList;
typedef CAObjHandle ExcelObj_UserAccess;
typedef CAObjHandle ExcelObj_DiagramNodes;
typedef CAObjHandle ExcelObj_ListColumns;
typedef CAObjHandle ExcelObj_ListRows;
typedef CAObjHandle ExcelObj_ListColumn;
typedef CAObjHandle ExcelObj_ListDataFormat;
typedef CAObjHandle ExcelObj_ListRow;
typedef CAObjHandle ExcelObj_XmlNamespace;
typedef CAObjHandle ExcelObj_XmlSchema;
typedef CAObjHandle ExcelObj_XmlSchemas;
typedef CAObjHandle ExcelObj_XmlDataBinding;
/* NICDBLD_END> Type Library Specific Types */

extern const IID Excel_IID_QueryTable;
extern const IID Excel_IID_App;
extern const IID Excel_IID_Chart;
extern const IID Excel_IID_Worksheet;
extern const IID Excel_IID_Global;
extern const IID Excel_IID_Workbook;
extern const IID Excel_IID_OLEObject;
extern const IID Excel_IID_RefreshEvents;
extern const IID Excel_IID_AppEvents;
extern const IID Excel_IID_ChartEvents;
extern const IID Excel_IID_DocEvents;
extern const IID Excel_IID_WorkbkEvents;
extern const IID Excel_IID_OLEObjectEvents;
extern const IID Excel_IID_Adjustments;
extern const IID Excel_IID_CalloutFormat;
extern const IID Excel_IID_ColorFormat;
extern const IID Excel_IID_LineFormat;
extern const IID Excel_IID_ShapeNode;
extern const IID Excel_IID_ShapeNodes;
extern const IID Excel_IID_PictureFmt;
extern const IID Excel_IID_ShadowFormat;
extern const IID Excel_IID_TextEffectFmt;
extern const IID Excel_IID_ThreeDFmt;
extern const IID Excel_IID_FillFormat;
extern const IID Excel_IID_DiagramNodes;
extern const IID Excel_IID_DiagramNodeChildren;
extern const IID Excel_IID_DiagramNode;
extern const IID Excel_IID_IRTDUpdateEvent;
extern const IID Excel_IID_IRtdServer;
extern const IID Excel_IID_Sheets;
extern const IID Excel_IID_Workbooks;
extern const IID Excel_IID_PublishObject;
extern const IID Excel_IID_DefaultWebOptions;
extern const IID Excel_IID_WebOptions;
extern const IID Excel_IID_TreeviewControl;
extern const IID Excel_IID_CubeField;
extern const IID Excel_IID_CubeFields;
extern const IID Excel_IID_Font;
extern const IID Excel_IID_Window;
extern const IID Excel_IID_Windows;
extern const IID Excel_IID_WorksheetFunction;
extern const IID Excel_IID_Range;
extern const IID Excel_IID_VPageBreak;
extern const IID Excel_IID_HPageBreak;
extern const IID Excel_IID_HPageBreaks;
extern const IID Excel_IID_VPageBreaks;
extern const IID Excel_IID_RecentFile;
extern const IID Excel_IID_RecentFiles;
extern const IID Excel_IID_Style;
extern const IID Excel_IID_Styles;
extern const IID Excel_IID_Borders;
extern const IID Excel_IID_AddIn;
extern const IID Excel_IID_AddIns;
extern const IID Excel_IID_Toolbar;
extern const IID Excel_IID_Toolbars;
extern const IID Excel_IID_ToolbarButton;
extern const IID Excel_IID_ToolbarButtons;
extern const IID Excel_IID_Areas;
extern const IID Excel_IID_MenuBars;
extern const IID Excel_IID_MenuBar;
extern const IID Excel_IID_Menus;
extern const IID Excel_IID_Menu;
extern const IID Excel_IID_MenuItems;
extern const IID Excel_IID_MenuItem;
extern const IID Excel_IID_Charts;
extern const IID Excel_IID_DrawingObjects;
extern const IID Excel_IID_PivotCache;
extern const IID Excel_IID_PivotCaches;
extern const IID Excel_IID_PivotFormula;
extern const IID Excel_IID_PivotFormulas;
extern const IID Excel_IID_PivotTable;
extern const IID Excel_IID_PivotTables;
extern const IID Excel_IID_PivotField;
extern const IID Excel_IID_PivotFields;
extern const IID Excel_IID_CalculatedFields;
extern const IID Excel_IID_PivotItem;
extern const IID Excel_IID_PivotItems;
extern const IID Excel_IID_CalculatedItems;
extern const IID Excel_IID_Characters;
extern const IID Excel_IID_Dialogs;
extern const IID Excel_IID_Dialog;
extern const IID Excel_IID_SoundNote;
extern const IID Excel_IID_Button;
extern const IID Excel_IID_Buttons;
extern const IID Excel_IID_CheckBox;
extern const IID Excel_IID_CheckBoxes;
extern const IID Excel_IID_OptionButton;
extern const IID Excel_IID_OptionButtons;
extern const IID Excel_IID_EditBox;
extern const IID Excel_IID_EditBoxes;
extern const IID Excel_IID_ScrollBar;
extern const IID Excel_IID_ScrollBars;
extern const IID Excel_IID_ListBox;
extern const IID Excel_IID_ListBoxes;
extern const IID Excel_IID_GroupBox;
extern const IID Excel_IID_GroupBoxes;
extern const IID Excel_IID_DropDown;
extern const IID Excel_IID_DropDowns;
extern const IID Excel_IID_Spinner;
extern const IID Excel_IID_Spinners;
extern const IID Excel_IID_DialogFrame;
extern const IID Excel_IID_Label;
extern const IID Excel_IID_Labels;
extern const IID Excel_IID_Panes;
extern const IID Excel_IID_Pane;
extern const IID Excel_IID_Scenarios;
extern const IID Excel_IID_Scenario;
extern const IID Excel_IID_GroupObject;
extern const IID Excel_IID_GroupObjects;
extern const IID Excel_IID_Line;
extern const IID Excel_IID_Lines;
extern const IID Excel_IID_Rectangle;
extern const IID Excel_IID_Rectangles;
extern const IID Excel_IID_Oval;
extern const IID Excel_IID_Ovals;
extern const IID Excel_IID_Arc;
extern const IID Excel_IID_Arcs;
extern const IID Excel_IID_OLEObjects;
extern const IID Excel_IID_TextBox;
extern const IID Excel_IID_TextBoxes;
extern const IID Excel_IID_Picture;
extern const IID Excel_IID_Pictures;
extern const IID Excel_IID_Drawing;
extern const IID Excel_IID_Drawings;
extern const IID Excel_IID_RoutingSlip;
extern const IID Excel_IID_Outline;
extern const IID Excel_IID_Module;
extern const IID Excel_IID_Modules;
extern const IID Excel_IID_DialogSheet;
extern const IID Excel_IID_DialogSheets;
extern const IID Excel_IID_Worksheets;
extern const IID Excel_IID_PageSetup;
extern const IID Excel_IID_Names;
extern const IID Excel_IID_Name;
extern const IID Excel_IID_ChartObject;
extern const IID Excel_IID_ChartObjects;
extern const IID Excel_IID_Mailer;
extern const IID Excel_IID_CustomViews;
extern const IID Excel_IID_CustomView;
extern const IID Excel_IID_FormatConditions;
extern const IID Excel_IID_FormatCondition;
extern const IID Excel_IID_Comments;
extern const IID Excel_IID_Comment;
extern const IID Excel_IID_QueryTables;
extern const IID Excel_IID_Parameter;
extern const IID Excel_IID_Parameters;
extern const IID Excel_IID_ODBCError;
extern const IID Excel_IID_ODBCErrors;
extern const IID Excel_IID_Validation;
extern const IID Excel_IID_Hyperlinks;
extern const IID Excel_IID_Hyperlink;
extern const IID Excel_IID_AutoFilter;
extern const IID Excel_IID_Filters;
extern const IID Excel_IID_Filter;
extern const IID Excel_IID_AutoCorrect;
extern const IID Excel_IID_Border;
extern const IID Excel_IID_Interior;
extern const IID Excel_IID_ChartFillFormat;
extern const IID Excel_IID_ChartColorFormat;
extern const IID Excel_IID_Axis;
extern const IID Excel_IID_ChartTitle;
extern const IID Excel_IID_AxisTitle;
extern const IID Excel_IID_ChartGroup;
extern const IID Excel_IID_ChartGroups;
extern const IID Excel_IID_Axes;
extern const IID Excel_IID_Points;
extern const IID Excel_IID_Point;
extern const IID Excel_IID_Series;
extern const IID Excel_IID_SeriesCollection;
extern const IID Excel_IID_DataLabel;
extern const IID Excel_IID_DataLabels;
extern const IID Excel_IID_LegendEntry;
extern const IID Excel_IID_LegendEntries;
extern const IID Excel_IID_LegendKey;
extern const IID Excel_IID_Trendlines;
extern const IID Excel_IID_Trendline;
extern const IID Excel_IID_Corners;
extern const IID Excel_IID_SeriesLines;
extern const IID Excel_IID_HiLoLines;
extern const IID Excel_IID_Gridlines;
extern const IID Excel_IID_DropLines;
extern const IID Excel_IID_LeaderLines;
extern const IID Excel_IID_UpBars;
extern const IID Excel_IID_DownBars;
extern const IID Excel_IID_Floor;
extern const IID Excel_IID_Walls;
extern const IID Excel_IID_TickLabels;
extern const IID Excel_IID_PlotArea;
extern const IID Excel_IID_ChartArea;
extern const IID Excel_IID_Legend;
extern const IID Excel_IID_ErrorBars;
extern const IID Excel_IID_DataTable;
extern const IID Excel_IID_Phonetic;
extern const IID Excel_IID_Shape;
extern const IID Excel_IID_Shapes;
extern const IID Excel_IID_ShapeRange;
extern const IID Excel_IID_GroupShapes;
extern const IID Excel_IID_TextFrame;
extern const IID Excel_IID_ConnectorFormat;
extern const IID Excel_IID_FreeformBuilder;
extern const IID Excel_IID_ControlFormat;
extern const IID Excel_IID_OLEFormat;
extern const IID Excel_IID_LinkFormat;
extern const IID Excel_IID_PublishObjects;
extern const IID Excel_IID_OLEDBError;
extern const IID Excel_IID_OLEDBErrors;
extern const IID Excel_IID_Phonetics;
extern const IID Excel_IID_PivotLayout;
extern const IID Excel_IID_DisplayUnitLabel;
extern const IID Excel_IID_CellFormat;
extern const IID Excel_IID_UsedObjects;
extern const IID Excel_IID_CustomProperties;
extern const IID Excel_IID_CustomProperty;
extern const IID Excel_IID_CalculatedMembers;
extern const IID Excel_IID_CalculatedMember;
extern const IID Excel_IID_Watches;
extern const IID Excel_IID_Watch;
extern const IID Excel_IID_PivotCell;
extern const IID Excel_IID_Graphic;
extern const IID Excel_IID_AutoRecover;
extern const IID Excel_IID_ErrorCheckingOptions;
extern const IID Excel_IID_Errors;
extern const IID Excel_IID_Error;
extern const IID Excel_IID_SmartTagAction;
extern const IID Excel_IID_SmartTagActions;
extern const IID Excel_IID_SmartTag;
extern const IID Excel_IID_SmartTags;
extern const IID Excel_IID_SmartTagRecognizer;
extern const IID Excel_IID_SmartTagRecognizers;
extern const IID Excel_IID_SmartTagOptions;
extern const IID Excel_IID_SpellingOptions;
extern const IID Excel_IID_Speech;
extern const IID Excel_IID_Protection;
extern const IID Excel_IID_PivotItemList;
extern const IID Excel_IID_Tab;
extern const IID Excel_IID_AllowEditRanges;
extern const IID Excel_IID_AllowEditRange;
extern const IID Excel_IID_UserAccessList;
extern const IID Excel_IID_UserAccess;
extern const IID Excel_IID_RTD;
extern const IID Excel_IID_Diagram;
extern const IID Excel_IID_ListObjects;
extern const IID Excel_IID_ListObject;
extern const IID Excel_IID_ListColumns;
extern const IID Excel_IID_ListColumn;
extern const IID Excel_IID_ListRows;
extern const IID Excel_IID_ListRow;
extern const IID Excel_IID_XmlNamespace;
extern const IID Excel_IID_XmlNamespaces;
extern const IID Excel_IID_XmlDataBinding;
extern const IID Excel_IID_XmlSchema;
extern const IID Excel_IID_XmlSchemas;
extern const IID Excel_IID_XmlMap;
extern const IID Excel_IID_XmlMaps;
extern const IID Excel_IID_ListDataFormat;
extern const IID Excel_IID_XPath;

HRESULT CVIFUNC Excel_Get_ApplicationProperty (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               unsigned int propertyID,
                                               unsigned int propertyType,
                                               void *value);

HRESULT CVIFUNC Excel_Set_ApplicationProperty (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               unsigned int propertyID,
                                               unsigned int propertyType, ...);

HRESULT CVIFUNC Excel_Set_ApplicationPropertyByRef (CAObjHandle objectHandle,
                                                    ERRORINFO *errorInfo,
                                                    unsigned int propertyID,
                                                    unsigned int propertyType,
                                                    ...);

HRESULT CVIFUNC Excel_Get_WorksheetProperty (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             unsigned int propertyID,
                                             unsigned int propertyType,
                                             void *value);

HRESULT CVIFUNC Excel_Set_WorksheetProperty (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             unsigned int propertyID,
                                             unsigned int propertyType, ...);

HRESULT CVIFUNC Excel_Get_GlobalProperty (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          unsigned int propertyID,
                                          unsigned int propertyType, void *value);

HRESULT CVIFUNC Excel_Set_GlobalProperty (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          unsigned int propertyID,
                                          unsigned int propertyType, ...);

HRESULT CVIFUNC Excel_Get_WorkbookProperty (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            unsigned int propertyID,
                                            unsigned int propertyType,
                                            void *value);

HRESULT CVIFUNC Excel_Set_WorkbookProperty (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            unsigned int propertyID,
                                            unsigned int propertyType, ...);

HRESULT CVIFUNC Excel_GetSheetsProperty (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         unsigned int propertyID,
                                         unsigned int propertyType, void *value);

HRESULT CVIFUNC Excel_SetSheetsProperty (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         unsigned int propertyID,
                                         unsigned int propertyType, ...);

HRESULT CVIFUNC Excel_GetWorkbooksProperty (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            unsigned int propertyID,
                                            unsigned int propertyType,
                                            void *value);

HRESULT CVIFUNC Excel_GetFontProperty (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       unsigned int propertyID,
                                       unsigned int propertyType, void *value);

HRESULT CVIFUNC Excel_SetFontProperty (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       unsigned int propertyID,
                                       unsigned int propertyType, ...);

HRESULT CVIFUNC Excel_GetRangeProperty (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        unsigned int propertyID,
                                        unsigned int propertyType, void *value);

HRESULT CVIFUNC Excel_SetRangeProperty (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        unsigned int propertyID,
                                        unsigned int propertyType, ...);

HRESULT CVIFUNC Excel_NewApp (const char *server, int supportMultithreading,
                              LCID locale, int reserved,
                              CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_OpenApp (const char *fileName, const char *server,
                               int supportMultithreading, LCID locale,
                               int reserved, CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_ActiveApp (const char *server, int supportMultithreading,
                                 LCID locale, int reserved,
                                 CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_AppCalculate (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppDDEExecute (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, long channel,
                                     const char *string);

HRESULT CVIFUNC Excel_AppDDEInitiate (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, const char *app,
                                      const char *topic, long *returnValue);

HRESULT CVIFUNC Excel_AppDDEPoke (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  long channel, VARIANT item, VARIANT data);

HRESULT CVIFUNC Excel_AppDDERequest (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, long channel,
                                     const char *item, VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDDETerminate (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, long channel);

HRESULT CVIFUNC Excel_AppEvaluate (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT name,
                                   VARIANT *returnValue);

HRESULT CVIFUNC Excel_App_Evaluate (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT name,
                                    VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppExecuteExcel4Macro (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *string,
                                             VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppIntersect (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, ExcelObj_Range arg1,
                                    ExcelObj_Range arg2, VARIANT arg3,
                                    VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                    VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                    VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                    VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                    VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                    VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                    VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                    VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                    VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                    ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_AppRange (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT cell1, VARIANT cell2,
                                ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_AppRun (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                              VARIANT macro, VARIANT arg1, VARIANT arg2,
                              VARIANT arg3, VARIANT arg4, VARIANT arg5,
                              VARIANT arg6, VARIANT arg7, VARIANT arg8,
                              VARIANT arg9, VARIANT arg10, VARIANT arg11,
                              VARIANT arg12, VARIANT arg13, VARIANT arg14,
                              VARIANT arg15, VARIANT arg16, VARIANT arg17,
                              VARIANT arg18, VARIANT arg19, VARIANT arg20,
                              VARIANT arg21, VARIANT arg22, VARIANT arg23,
                              VARIANT arg24, VARIANT arg25, VARIANT arg26,
                              VARIANT arg27, VARIANT arg28, VARIANT arg29,
                              VARIANT arg30, VARIANT *returnValue);

HRESULT CVIFUNC Excel_App_Run2 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT macro, VARIANT arg1, VARIANT arg2,
                                VARIANT arg3, VARIANT arg4, VARIANT arg5,
                                VARIANT arg6, VARIANT arg7, VARIANT arg8,
                                VARIANT arg9, VARIANT arg10, VARIANT arg11,
                                VARIANT arg12, VARIANT arg13, VARIANT arg14,
                                VARIANT arg15, VARIANT arg16, VARIANT arg17,
                                VARIANT arg18, VARIANT arg19, VARIANT arg20,
                                VARIANT arg21, VARIANT arg22, VARIANT arg23,
                                VARIANT arg24, VARIANT arg25, VARIANT arg26,
                                VARIANT arg27, VARIANT arg28, VARIANT arg29,
                                VARIANT arg30, VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppSendKeys (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT keys,
                                   VARIANT wait);

HRESULT CVIFUNC Excel_AppShortcutMenus (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, long index,
                                        ExcelObj_Menu *returnValue);

HRESULT CVIFUNC Excel_AppUnion (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                ExcelObj_Range arg1, ExcelObj_Range arg2,
                                VARIANT arg3, VARIANT arg4, VARIANT arg5,
                                VARIANT arg6, VARIANT arg7, VARIANT arg8,
                                VARIANT arg9, VARIANT arg10, VARIANT arg11,
                                VARIANT arg12, VARIANT arg13, VARIANT arg14,
                                VARIANT arg15, VARIANT arg16, VARIANT arg17,
                                VARIANT arg18, VARIANT arg19, VARIANT arg20,
                                VARIANT arg21, VARIANT arg22, VARIANT arg23,
                                VARIANT arg24, VARIANT arg25, VARIANT arg26,
                                VARIANT arg27, VARIANT arg28, VARIANT arg29,
                                VARIANT arg30, ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_AppActivateMicrosoftApp (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               enum ExcelEnum_XlMSApplication index);

HRESULT CVIFUNC Excel_AppAddChartAutoFormat (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo, VARIANT chart,
                                             const char *name,
                                             VARIANT description);

HRESULT CVIFUNC Excel_AppAddCustomList (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT listArray,
                                        VARIANT byRow);

HRESULT CVIFUNC Excel_AppCaller (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT index, VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppCentimetersToPoints (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              double centimeters,
                                              double *returnValue);

HRESULT CVIFUNC Excel_AppCheckSpelling (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, const char *word,
                                        VARIANT customDictionary,
                                        VARIANT ignoreUppercase,
                                        VBOOL *returnValue);

HRESULT CVIFUNC Excel_AppClipboardFormats (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppConvertFormula (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT formula,
                                         enum ExcelEnum_XlReferenceStyle fromReferenceStyle,
                                         VARIANT toReferenceStyle,
                                         VARIANT toAbsolute, VARIANT relativeTo,
                                         VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy1 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                 VARIANT arg4, VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy2 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                 VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                 VARIANT arg7, VARIANT arg8,
                                 VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy3 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy4 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                 VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                 VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                 VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                 VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                 VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy5 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                 VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                 VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                 VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                 VARIANT arg13, VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy6 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy7 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy8 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT arg1, VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy9 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppDummy10 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT arg, VBOOL *returnValue);

HRESULT CVIFUNC Excel_AppDummy11 (CAObjHandle objectHandle, ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppDeleteChartAutoFormat (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                const char *name);

HRESULT CVIFUNC Excel_AppDeleteCustomList (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, long listNum);

HRESULT CVIFUNC Excel_AppDoubleClick (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppFileConverters (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index1,
                                         VARIANT index2, VARIANT *returnValue);

HRESULT CVIFUNC Excel_App_FindFile (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppGetCustomListContents (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                long listNum,
                                                VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppGetCustomListNum (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           VARIANT listArray, long *returnValue);

HRESULT CVIFUNC Excel_AppGetOpenFilename (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT fileFilter,
                                          VARIANT filterIndex, VARIANT title,
                                          VARIANT buttonText,
                                          VARIANT multiSelect,
                                          VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppGetSaveAsFilename (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            VARIANT initialFilename,
                                            VARIANT fileFilter,
                                            VARIANT filterIndex, VARIANT title,
                                            VARIANT buttonText,
                                            VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppGoto (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                               VARIANT reference, VARIANT scroll);

HRESULT CVIFUNC Excel_AppHelp (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                               VARIANT helpFile, VARIANT helpContextID);

HRESULT CVIFUNC Excel_AppInchesToPoints (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, double inches,
                                         double *returnValue);

HRESULT CVIFUNC Excel_AppInputBox (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, const char *prompt,
                                   VARIANT title, VARIANT _default, VARIANT left,
                                   VARIANT top, VARIANT helpFile,
                                   VARIANT helpContextID, VARIANT type,
                                   VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppInternational (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT index,
                                        VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppMacroOptions (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT macro,
                                       VARIANT description, VARIANT hasMenu,
                                       VARIANT menuText, VARIANT hasShortcutKey,
                                       VARIANT shortcutKey, VARIANT category,
                                       VARIANT statusBar, VARIANT helpContextID,
                                       VARIANT helpFile);

HRESULT CVIFUNC Excel_AppMailLogoff (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppMailLogon (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT name,
                                    VARIANT password, VARIANT downloadNewMail);

HRESULT CVIFUNC Excel_AppNextLetter (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_AppOnKey (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                const char *key, VARIANT procedure);

HRESULT CVIFUNC Excel_AppOnRepeat (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, const char *text,
                                   const char *procedure);

HRESULT CVIFUNC Excel_AppOnTime (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT earliestTime, const char *procedure,
                                 VARIANT latestTime, VARIANT schedule);

HRESULT CVIFUNC Excel_AppOnUndo (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 const char *text, const char *procedure);

HRESULT CVIFUNC Excel_AppPreviousSelections (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo, VARIANT index,
                                             VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppQuit (CAObjHandle objectHandle, ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppRecordMacro (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT basicCode,
                                      VARIANT xlmCode);

HRESULT CVIFUNC Excel_AppRegisteredFunctions (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT index1, VARIANT index2,
                                              VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppRegisterXLL (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, const char *filename,
                                      VBOOL *returnValue);

HRESULT CVIFUNC Excel_AppRepeat (CAObjHandle objectHandle, ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppResetTipWizard (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppSave (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                               VARIANT filename);

HRESULT CVIFUNC Excel_AppSaveWorkspace (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT filename);

HRESULT CVIFUNC Excel_AppSetDefaultChart (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT formatName, VARIANT gallery);

HRESULT CVIFUNC Excel_AppUndo (CAObjHandle objectHandle, ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppVolatile (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT _volatile);

HRESULT CVIFUNC Excel_App_Wait (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT time);

HRESULT CVIFUNC Excel_App_WSFunction (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT arg1,
                                      VARIANT arg2, VARIANT arg3, VARIANT arg4,
                                      VARIANT arg5, VARIANT arg6, VARIANT arg7,
                                      VARIANT arg8, VARIANT arg9, VARIANT arg10,
                                      VARIANT arg11, VARIANT arg12,
                                      VARIANT arg13, VARIANT arg14,
                                      VARIANT arg15, VARIANT arg16,
                                      VARIANT arg17, VARIANT arg18,
                                      VARIANT arg19, VARIANT arg20,
                                      VARIANT arg21, VARIANT arg22,
                                      VARIANT arg23, VARIANT arg24,
                                      VARIANT arg25, VARIANT arg26,
                                      VARIANT arg27, VARIANT arg28,
                                      VARIANT arg29, VARIANT arg30,
                                      VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppWait (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                               VARIANT time, VBOOL *returnValue);

HRESULT CVIFUNC Excel_AppGetPhonetic (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT text,
                                      char **returnValue);

HRESULT CVIFUNC Excel_AppDummy12 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  ExcelObj_PivotTable p1, ExcelObj_PivotTable p2);

HRESULT CVIFUNC Excel_AppCalculateFull (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppFindFile (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VBOOL *returnValue);

HRESULT CVIFUNC Excel_AppDummy13 (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                  VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                  VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                  VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                  VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                  VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                  VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                  VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                  VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                  VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                  VARIANT *returnValue);

HRESULT CVIFUNC Excel_AppFileDialog (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     enum ExcelEnum_MsoFileDialogType fileDialogType,
                                     ExcelObj_FileDialog *returnValue);

HRESULT CVIFUNC Excel_AppDummy14 (CAObjHandle objectHandle, ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppCalculateFullRebuild (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_AppCheckAbort (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT keepAbort);

HRESULT CVIFUNC Excel_AppDisplayXMLSourcePane (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VARIANT xmlMap);

HRESULT CVIFUNC Excel_AppSupport (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  CAObjHandle object, long ID, VARIANT arg,
                                  VARIANT *returnValue);

HRESULT CVIFUNC Excel_NewWorksheet (int panel, const char *label, int top,
                                    int left, int *controlID, int *UILError);

HRESULT CVIFUNC Excel_OpenWorksheet (const char *fileName, int panel,
                                     const char *label, int top, int left,
                                     int *controlID, int *UILError);

HRESULT CVIFUNC Excel_WorksheetActivate (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetCopy (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT before,
                                     VARIANT after);

HRESULT CVIFUNC Excel_WorksheetDelete (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetMove (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT before,
                                     VARIANT after);

HRESULT CVIFUNC Excel_Worksheet_PrintOut (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT from,
                                          VARIANT to, VARIANT copies,
                                          VARIANT preview, VARIANT activePrinter,
                                          VARIANT printToFile, VARIANT collate);

HRESULT CVIFUNC Excel_WorksheetPrintPreview (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             VARIANT enableChanges);

HRESULT CVIFUNC Excel_Worksheet_Protect (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT password,
                                         VARIANT drawingObjects,
                                         VARIANT contents, VARIANT scenarios,
                                         VARIANT userInterfaceOnly);

HRESULT CVIFUNC Excel_Worksheet_SaveAs (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        const char *filename, VARIANT fileFormat,
                                        VARIANT password,
                                        VARIANT writeResPassword,
                                        VARIANT readOnlyRecommended,
                                        VARIANT createBackup, VARIANT addToMru,
                                        VARIANT textCodepage,
                                        VARIANT textVisualLayout);

HRESULT CVIFUNC Excel_WorksheetSelect (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT replace);

HRESULT CVIFUNC Excel_WorksheetUnprotect (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT password);

HRESULT CVIFUNC Excel_WorksheetArcs (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT index,
                                     CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetSetBackgroundPicture (CAObjHandle objectHandle,
                                                     ERRORINFO *errorInfo,
                                                     const char *filename);

HRESULT CVIFUNC Excel_WorksheetButtons (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT index,
                                        CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetCalculate (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetChartObjects (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo, VARIANT index,
                                             CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetCheckBoxes (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetCheckSpelling (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT customDictionary,
                                              VARIANT ignoreUppercase,
                                              VARIANT alwaysSuggest,
                                              VARIANT spellLang);

HRESULT CVIFUNC Excel_WorksheetClearArrows (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetDrawings (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetDrawingObjects (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VARIANT index,
                                               CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetDropDowns (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT index,
                                          CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetEvaluate (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT name,
                                         VARIANT *returnValue);

HRESULT CVIFUNC Excel_Worksheet_Evaluate (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT name,
                                          VARIANT *returnValue);

HRESULT CVIFUNC Excel_WorksheetResetAllPageBreaks (CAObjHandle objectHandle,
                                                   ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetGroupBoxes (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetGroupObjects (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo, VARIANT index,
                                             CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetLabels (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT index,
                                       CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetLines (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT index,
                                      CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetListBoxes (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT index,
                                          CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetOLEObjects (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetOptionButtons (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT index,
                                              CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetOvals (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT index,
                                      CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetPaste (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT destination,
                                      VARIANT link);

HRESULT CVIFUNC Excel_Worksheet_PasteSpecial (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT format, VARIANT link,
                                              VARIANT displayAsIcon,
                                              VARIANT iconFileName,
                                              VARIANT iconIndex,
                                              VARIANT iconLabel);

HRESULT CVIFUNC Excel_WorksheetPictures (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetPivotTables (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo, VARIANT index,
                                            CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetPivotTableWizard (CAObjHandle objectHandle,
                                                 ERRORINFO *errorInfo,
                                                 VARIANT sourceType,
                                                 VARIANT sourceData,
                                                 VARIANT tableDestination,
                                                 VARIANT tableName,
                                                 VARIANT rowGrand,
                                                 VARIANT columnGrand,
                                                 VARIANT saveData,
                                                 VARIANT hasAutoFormat,
                                                 VARIANT autoPage,
                                                 VARIANT reserved,
                                                 VARIANT backgroundQuery,
                                                 VARIANT optimizeCache,
                                                 VARIANT pageFieldOrder,
                                                 VARIANT pageFieldWrapCount,
                                                 VARIANT readData,
                                                 VARIANT connection,
                                                 ExcelObj_PivotTable *returnValue);

HRESULT CVIFUNC Excel_WorksheetRange (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT cell1,
                                      VARIANT cell2, ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_WorksheetRectangles (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetScenarios (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT index,
                                          CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetScrollBars (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT index,
                                           CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetShowAllData (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetShowDataForm (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetSpinners (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetTextBoxes (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT index,
                                          CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_WorksheetClearCircles (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetCircleInvalid (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorksheetPrintOut (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT from,
                                         VARIANT to, VARIANT copies,
                                         VARIANT preview, VARIANT activePrinter,
                                         VARIANT printToFile, VARIANT collate,
                                         VARIANT prToFileName);

HRESULT CVIFUNC Excel_Worksheet_CheckSpelling (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VARIANT customDictionary,
                                               VARIANT ignoreUppercase,
                                               VARIANT alwaysSuggest,
                                               VARIANT spellLang,
                                               VARIANT ignoreFinalYaa,
                                               VARIANT spellScript);

HRESULT CVIFUNC Excel_WorksheetSaveAs (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       const char *filename, VARIANT fileFormat,
                                       VARIANT password,
                                       VARIANT writeResPassword,
                                       VARIANT readOnlyRecommended,
                                       VARIANT createBackup, VARIANT addToMru,
                                       VARIANT textCodepage,
                                       VARIANT textVisualLayout, VARIANT local);

HRESULT CVIFUNC Excel_WorksheetPasteSpecial (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             VARIANT format, VARIANT link,
                                             VARIANT displayAsIcon,
                                             VARIANT iconFileName,
                                             VARIANT iconIndex,
                                             VARIANT iconLabel,
                                             VARIANT noHTMLFormatting);

HRESULT CVIFUNC Excel_WorksheetProtect (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT password,
                                        VARIANT drawingObjects, VARIANT contents,
                                        VARIANT scenarios,
                                        VARIANT userInterfaceOnly,
                                        VARIANT allowFormattingCells,
                                        VARIANT allowFormattingColumns,
                                        VARIANT allowFormattingRows,
                                        VARIANT allowInsertingColumns,
                                        VARIANT allowInsertingRows,
                                        VARIANT allowInsertingHyperlinks,
                                        VARIANT allowDeletingColumns,
                                        VARIANT allowDeletingRows,
                                        VARIANT allowSorting,
                                        VARIANT allowFiltering,
                                        VARIANT allowUsingPivotTables);

HRESULT CVIFUNC Excel_WorksheetXmlDataQuery (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *XPath,
                                             VARIANT selectionNamespaces,
                                             VARIANT map,
                                             ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_WorksheetXmlMapQuery (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            const char *XPath,
                                            VARIANT selectionNamespaces,
                                            VARIANT map,
                                            ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_NewGlobal (const char *server, int supportMultithreading,
                                 LCID locale, int reserved,
                                 CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_OpenGlobal (const char *fileName, const char *server,
                                  int supportMultithreading, LCID locale,
                                  int reserved, CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_ActiveGlobal (const char *server,
                                    int supportMultithreading, LCID locale,
                                    int reserved, CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_GlobalCalculate (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_GlobalDDEExecute (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, long channel,
                                        const char *string);

HRESULT CVIFUNC Excel_GlobalDDEInitiate (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, const char *app,
                                         const char *topic, long *returnValue);

HRESULT CVIFUNC Excel_GlobalDDEPoke (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, long channel,
                                     VARIANT item, VARIANT data);

HRESULT CVIFUNC Excel_GlobalDDERequest (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, long channel,
                                        const char *item, VARIANT *returnValue);

HRESULT CVIFUNC Excel_GlobalDDETerminate (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, long channel);

HRESULT CVIFUNC Excel_GlobalEvaluate (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT name,
                                      VARIANT *returnValue);

HRESULT CVIFUNC Excel_Global_Evaluate (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT name,
                                       VARIANT *returnValue);

HRESULT CVIFUNC Excel_GlobalExecuteExcel4Macro (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                const char *string,
                                                VARIANT *returnValue);

HRESULT CVIFUNC Excel_GlobalIntersect (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, ExcelObj_Range arg1,
                                       ExcelObj_Range arg2, VARIANT arg3,
                                       VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                       VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                       VARIANT arg10, VARIANT arg11,
                                       VARIANT arg12, VARIANT arg13,
                                       VARIANT arg14, VARIANT arg15,
                                       VARIANT arg16, VARIANT arg17,
                                       VARIANT arg18, VARIANT arg19,
                                       VARIANT arg20, VARIANT arg21,
                                       VARIANT arg22, VARIANT arg23,
                                       VARIANT arg24, VARIANT arg25,
                                       VARIANT arg26, VARIANT arg27,
                                       VARIANT arg28, VARIANT arg29,
                                       VARIANT arg30,
                                       ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_GlobalRange (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT cell1,
                                   VARIANT cell2, ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_GlobalRun (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT macro, VARIANT arg1, VARIANT arg2,
                                 VARIANT arg3, VARIANT arg4, VARIANT arg5,
                                 VARIANT arg6, VARIANT arg7, VARIANT arg8,
                                 VARIANT arg9, VARIANT arg10, VARIANT arg11,
                                 VARIANT arg12, VARIANT arg13, VARIANT arg14,
                                 VARIANT arg15, VARIANT arg16, VARIANT arg17,
                                 VARIANT arg18, VARIANT arg19, VARIANT arg20,
                                 VARIANT arg21, VARIANT arg22, VARIANT arg23,
                                 VARIANT arg24, VARIANT arg25, VARIANT arg26,
                                 VARIANT arg27, VARIANT arg28, VARIANT arg29,
                                 VARIANT arg30, VARIANT *returnValue);

HRESULT CVIFUNC Excel_Global_Run2 (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT macro,
                                   VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                   VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                   VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                   VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                   VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                   VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                   VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                   VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                   VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                   VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                   VARIANT *returnValue);

HRESULT CVIFUNC Excel_GlobalSendKeys (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT keys,
                                      VARIANT wait);

HRESULT CVIFUNC Excel_GlobalShortcutMenus (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, long index,
                                           ExcelObj_Menu *returnValue);

HRESULT CVIFUNC Excel_GlobalUnion (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, ExcelObj_Range arg1,
                                   ExcelObj_Range arg2, VARIANT arg3,
                                   VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                   VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                   VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                   VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                   VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                   VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                   VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                   VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                   VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                   ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_NewWorkbook (const char *server, int supportMultithreading,
                                   LCID locale, int reserved,
                                   CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_OpenWorkbook (const char *fileName, const char *server,
                                    int supportMultithreading, LCID locale,
                                    int reserved, CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_ActiveWorkbook (const char *server,
                                      int supportMultithreading, LCID locale,
                                      int reserved, CAObjHandle *objectHandle);

HRESULT CVIFUNC Excel_WorkbookActivate (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookChangeFileAccess (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                enum ExcelEnum_XlFileAccess mode,
                                                VARIANT writePassword,
                                                VARIANT notify);

HRESULT CVIFUNC Excel_WorkbookChangeLink (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, const char *name,
                                          const char *newName,
                                          enum ExcelEnum_XlLinkType type);

HRESULT CVIFUNC Excel_WorkbookClose (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT saveChanges,
                                     VARIANT filename, VARIANT routeWorkbook);

HRESULT CVIFUNC Excel_WorkbookGetColors (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         VARIANT *returnValue);

HRESULT CVIFUNC Excel_WorkbookSetColors (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         VARIANT newValue);

HRESULT CVIFUNC Excel_WorkbookDeleteNumberFormat (CAObjHandle objectHandle,
                                                  ERRORINFO *errorInfo,
                                                  const char *numberFormat);

HRESULT CVIFUNC Excel_WorkbookExclusiveAccess (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VBOOL *returnValue);

HRESULT CVIFUNC Excel_WorkbookForwardMailer (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookLinkInfo (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, const char *name,
                                        enum ExcelEnum_XlLinkInfo linkInfo,
                                        VARIANT type, VARIANT editionRef,
                                        VARIANT *returnValue);

HRESULT CVIFUNC Excel_WorkbookLinkSources (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT type,
                                           VARIANT *returnValue);

HRESULT CVIFUNC Excel_WorkbookMergeWorkbook (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             VARIANT filename);

HRESULT CVIFUNC Excel_WorkbookNewWindow (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         ExcelObj_Window *returnValue);

HRESULT CVIFUNC Excel_WorkbookOpenLinks (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, const char *name,
                                         VARIANT readOnly, VARIANT type);

HRESULT CVIFUNC Excel_WorkbookPivotCaches (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           ExcelObj_PivotCaches *returnValue);

HRESULT CVIFUNC Excel_WorkbookPost (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT destName);

HRESULT CVIFUNC Excel_Workbook_PrintOut (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT from,
                                         VARIANT to, VARIANT copies,
                                         VARIANT preview, VARIANT activePrinter,
                                         VARIANT printToFile, VARIANT collate);

HRESULT CVIFUNC Excel_WorkbookPrintPreview (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            VARIANT enableChanges);

HRESULT CVIFUNC Excel_Workbook_Protect (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT password,
                                        VARIANT structure, VARIANT windows);

HRESULT CVIFUNC Excel_WorkbookProtectSharing (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT filename, VARIANT password,
                                              VARIANT writeResPassword,
                                              VARIANT readOnlyRecommended,
                                              VARIANT createBackup,
                                              VARIANT sharingPassword);

HRESULT CVIFUNC Excel_WorkbookRefreshAll (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookReply (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookReplyAll (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookRemoveUser (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, long index);

HRESULT CVIFUNC Excel_WorkbookRoute (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookRunAutoMacros (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             enum ExcelEnum_XlRunAutoMacro which);

HRESULT CVIFUNC Excel_WorkbookSave (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_Workbook_SaveAs (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT filename,
                                       VARIANT fileFormat, VARIANT password,
                                       VARIANT writeResPassword,
                                       VARIANT readOnlyRecommended,
                                       VARIANT createBackup,
                                       enum ExcelEnum_XlSaveAsAccessMode accessMode,
                                       VARIANT conflictResolution,
                                       VARIANT addToMru, VARIANT textCodepage,
                                       VARIANT textVisualLayout);

HRESULT CVIFUNC Excel_WorkbookSaveCopyAs (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT filename);

HRESULT CVIFUNC Excel_WorkbookSendMail (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT recipients,
                                        VARIANT subject, VARIANT returnReceipt);

HRESULT CVIFUNC Excel_WorkbookSendMailer (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT fileFormat,
                                          enum ExcelEnum_XlPriority priority);

HRESULT CVIFUNC Excel_WorkbookSetLinkOnData (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *name, VARIANT procedure);

HRESULT CVIFUNC Excel_WorkbookUnprotect (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT password);

HRESULT CVIFUNC Excel_WorkbookUnprotectSharing (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT sharingPassword);

HRESULT CVIFUNC Excel_WorkbookUpdateFromFile (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookUpdateLink (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo, VARIANT name,
                                          VARIANT type);

HRESULT CVIFUNC Excel_WorkbookHighlightChangesOptions (CAObjHandle objectHandle,
                                                       ERRORINFO *errorInfo,
                                                       VARIANT when, VARIANT who,
                                                       VARIANT where);

HRESULT CVIFUNC Excel_WorkbookPurgeChangeHistoryNow (CAObjHandle objectHandle,
                                                     ERRORINFO *errorInfo,
                                                     long days,
                                                     VARIANT sharingPassword);

HRESULT CVIFUNC Excel_WorkbookAcceptAllChanges (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT when, VARIANT who,
                                                VARIANT where);

HRESULT CVIFUNC Excel_WorkbookRejectAllChanges (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT when, VARIANT who,
                                                VARIANT where);

HRESULT CVIFUNC Excel_WorkbookPivotTableWizard (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT sourceType,
                                                VARIANT sourceData,
                                                VARIANT tableDestination,
                                                VARIANT tableName,
                                                VARIANT rowGrand,
                                                VARIANT columnGrand,
                                                VARIANT saveData,
                                                VARIANT hasAutoFormat,
                                                VARIANT autoPage,
                                                VARIANT reserved,
                                                VARIANT backgroundQuery,
                                                VARIANT optimizeCache,
                                                VARIANT pageFieldOrder,
                                                VARIANT pageFieldWrapCount,
                                                VARIANT readData,
                                                VARIANT connection);

HRESULT CVIFUNC Excel_WorkbookResetColors (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookFollowHyperlink (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               const char *address,
                                               VARIANT subAddress,
                                               VARIANT newWindow,
                                               VARIANT addHistory,
                                               VARIANT extraInfo, VARIANT method,
                                               VARIANT headerInfo);

HRESULT CVIFUNC Excel_WorkbookAddToFavorites (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookPrintOut (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT from,
                                        VARIANT to, VARIANT copies,
                                        VARIANT preview, VARIANT activePrinter,
                                        VARIANT printToFile, VARIANT collate,
                                        VARIANT prToFileName);

HRESULT CVIFUNC Excel_WorkbookWebPagePreview (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookReloadAs (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        enum ExcelEnum_MsoEncoding encoding);

HRESULT CVIFUNC Excel_WorkbookDummy17 (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, long calcid);

HRESULT CVIFUNC Excel_Workbooksblt (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, const char *s);

HRESULT CVIFUNC Excel_WorkbookBreakLink (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, const char *name,
                                         enum ExcelEnum_XlLinkType type);

HRESULT CVIFUNC Excel_WorkbookDummy16 (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookSaveAs (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT filename,
                                      VARIANT fileFormat, VARIANT password,
                                      VARIANT writeResPassword,
                                      VARIANT readOnlyRecommended,
                                      VARIANT createBackup,
                                      enum ExcelEnum_XlSaveAsAccessMode accessMode,
                                      VARIANT conflictResolution,
                                      VARIANT addToMru, VARIANT textCodepage,
                                      VARIANT textVisualLayout, VARIANT local);

HRESULT CVIFUNC Excel_WorkbookCheckIn (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT saveChanges,
                                       VARIANT comments, VARIANT makePublic);

HRESULT CVIFUNC Excel_WorkbookCanCheckIn (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VBOOL *returnValue);

HRESULT CVIFUNC Excel_WorkbookSendForReview (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             VARIANT recipients, VARIANT subject,
                                             VARIANT showMessage,
                                             VARIANT includeAttachment);

HRESULT CVIFUNC Excel_WorkbookReplyWithChanges (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo,
                                                VARIANT showMessage);

HRESULT CVIFUNC Excel_WorkbookEndReview (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookSetPasswordEncryptionOptions (CAObjHandle objectHandle,
                                                            ERRORINFO *errorInfo,
                                                            VARIANT passwordEncryptionProvider,
                                                            VARIANT passwordEncryptionAlgorithm,
                                                            VARIANT passwordEncryptionKeyLength,
                                                            VARIANT passwordEncryptionFilePropertie);

HRESULT CVIFUNC Excel_WorkbookProtect (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT password,
                                       VARIANT structure, VARIANT windows);

HRESULT CVIFUNC Excel_WorkbookRecheckSmartTags (CAObjHandle objectHandle,
                                                ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbookSendFaxOverInternet (CAObjHandle objectHandle,
                                                   ERRORINFO *errorInfo,
                                                   VARIANT recipients,
                                                   VARIANT subject,
                                                   VARIANT showMessage);

HRESULT CVIFUNC Excel_WorkbookXmlImport (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, const char *url,
                                         ExcelObj_XmlMap *importMap,
                                         VARIANT overwrite, VARIANT destination,
                                         enum ExcelEnum_XlXmlImportResult *returnValue);

HRESULT CVIFUNC Excel_WorkbookXmlImportXml (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            const char *data,
                                            ExcelObj_XmlMap *importMap,
                                            VARIANT overwrite,
                                            VARIANT destination,
                                            enum ExcelEnum_XlXmlImportResult *returnValue);

HRESULT CVIFUNC Excel_WorkbookSaveAsXMLData (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *filename,
                                             ExcelObj_XmlMap map);

HRESULT CVIFUNC Excel_WorkbookToggleFormsDesign (CAObjHandle objectHandle,
                                                 ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_SheetsAdd (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT before, VARIANT after, VARIANT count,
                                 VARIANT type, CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_SheetsCopy (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT before, VARIANT after);

HRESULT CVIFUNC Excel_SheetsDelete (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_SheetsFillAcrossSheets (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              ExcelObj_Range range,
                                              enum ExcelEnum_XlFillWith type);

HRESULT CVIFUNC Excel_SheetsItem (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT index, CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_SheetsMove (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT before, VARIANT after);

HRESULT CVIFUNC Excel_Sheets_PrintOut (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT from,
                                       VARIANT to, VARIANT copies,
                                       VARIANT preview, VARIANT activePrinter,
                                       VARIANT printToFile, VARIANT collate);

HRESULT CVIFUNC Excel_SheetsPrintPreview (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT enableChanges);

HRESULT CVIFUNC Excel_SheetsSelect (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT replace);

HRESULT CVIFUNC Excel_Sheets_Default (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT index,
                                      CAObjHandle *returnValue);

HRESULT CVIFUNC Excel_SheetsPrintOut (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT from,
                                      VARIANT to, VARIANT copies,
                                      VARIANT preview, VARIANT activePrinter,
                                      VARIANT printToFile, VARIANT collate,
                                      VARIANT prToFileName);

HRESULT CVIFUNC Excel_WorkbooksAdd (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT template,
                                    ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_WorkbooksClose (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_WorkbooksItem (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT index,
                                     ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_Workbooks_Open (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, const char *filename,
                                      VARIANT updateLinks, VARIANT readOnly,
                                      VARIANT format, VARIANT password,
                                      VARIANT writeResPassword,
                                      VARIANT ignoreReadOnlyRecommended,
                                      VARIANT origin, VARIANT delimiter,
                                      VARIANT editable, VARIANT notify,
                                      VARIANT converter, VARIANT addToMru,
                                      ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_Workbooks__OpenText (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           const char *filename, VARIANT origin,
                                           VARIANT startRow, VARIANT dataType,
                                           enum ExcelEnum_XlTextQualifier textQualifier,
                                           VARIANT consecutiveDelimiter,
                                           VARIANT tab, VARIANT semicolon,
                                           VARIANT comma, VARIANT space,
                                           VARIANT other, VARIANT otherChar,
                                           VARIANT fieldInfo,
                                           VARIANT textVisualLayout);

HRESULT CVIFUNC Excel_Workbooks_Default (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT index,
                                         ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_Workbooks_OpenText (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          const char *filename, VARIANT origin,
                                          VARIANT startRow, VARIANT dataType,
                                          enum ExcelEnum_XlTextQualifier textQualifier,
                                          VARIANT consecutiveDelimiter,
                                          VARIANT tab, VARIANT semicolon,
                                          VARIANT comma, VARIANT space,
                                          VARIANT other, VARIANT otherChar,
                                          VARIANT fieldInfo,
                                          VARIANT textVisualLayout,
                                          VARIANT decimalSeparator,
                                          VARIANT thousandsSeparator);

HRESULT CVIFUNC Excel_WorkbooksOpen (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, const char *filename,
                                     VARIANT updateLinks, VARIANT readOnly,
                                     VARIANT format, VARIANT password,
                                     VARIANT writeResPassword,
                                     VARIANT ignoreReadOnlyRecommended,
                                     VARIANT origin, VARIANT delimiter,
                                     VARIANT editable, VARIANT notify,
                                     VARIANT converter, VARIANT addToMru,
                                     VARIANT local, VARIANT corruptLoad,
                                     ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_WorkbooksOpenText (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         const char *filename, VARIANT origin,
                                         VARIANT startRow, VARIANT dataType,
                                         enum ExcelEnum_XlTextQualifier textQualifier,
                                         VARIANT consecutiveDelimiter,
                                         VARIANT tab, VARIANT semicolon,
                                         VARIANT comma, VARIANT space,
                                         VARIANT other, VARIANT otherChar,
                                         VARIANT fieldInfo,
                                         VARIANT textVisualLayout,
                                         VARIANT decimalSeparator,
                                         VARIANT thousandsSeparator,
                                         VARIANT trailingMinusNumbers,
                                         VARIANT local);

HRESULT CVIFUNC Excel_WorkbooksOpenDatabase (CAObjHandle objectHandle,
                                             ERRORINFO *errorInfo,
                                             const char *filename,
                                             VARIANT commandText,
                                             VARIANT commandType,
                                             VARIANT backgroundQuery,
                                             VARIANT importDataAs,
                                             ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_WorkbooksCheckOut (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         const char *filename);

HRESULT CVIFUNC Excel_WorkbooksCanCheckOut (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            const char *filename,
                                            VBOOL *returnValue);

HRESULT CVIFUNC Excel_Workbooks_OpenXML (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         const char *filename,
                                         VARIANT stylesheets,
                                         ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_WorkbooksOpenXML (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        const char *filename,
                                        VARIANT stylesheets, VARIANT loadOption,
                                        ExcelObj_Workbook *returnValue);

HRESULT CVIFUNC Excel_RangeActivate (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeAddress (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT rowAbsolute,
                                    VARIANT columnAbsolute,
                                    enum ExcelEnum_XlReferenceStyle referenceStyle,
                                    VARIANT external, VARIANT relativeTo,
                                    char **returnValue);

HRESULT CVIFUNC Excel_RangeAddressLocal (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         VARIANT rowAbsolute,
                                         VARIANT columnAbsolute,
                                         enum ExcelEnum_XlReferenceStyle referenceStyle,
                                         VARIANT external, VARIANT relativeTo,
                                         char **returnValue);

HRESULT CVIFUNC Excel_RangeAdvancedFilter (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           enum ExcelEnum_XlFilterAction action,
                                           VARIANT criteriaRange,
                                           VARIANT copyToRange, VARIANT unique,
                                           VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeApplyNames (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT names,
                                       VARIANT ignoreRelativeAbsolute,
                                       VARIANT useRowColumnNames,
                                       VARIANT omitColumn, VARIANT omitRow,
                                       enum ExcelEnum_XlApplyNamesOrder order,
                                       VARIANT appendLast, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeApplyOutlineStyles (CAObjHandle objectHandle,
                                               ERRORINFO *errorInfo,
                                               VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeAutoComplete (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         const char *string, char **returnValue);

HRESULT CVIFUNC Excel_RangeAutoFill (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     ExcelObj_Range destination,
                                     enum ExcelEnum_XlAutoFillType type,
                                     VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeAutoFilter (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT field,
                                       VARIANT criteria1,
                                       enum ExcelEnum_XlAutoFilterOperator operator,
                                       VARIANT criteria2,
                                       VARIANT visibleDropDown,
                                       VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeAutoFit (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeAutoFormat (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       enum ExcelEnum_XlRangeAutoFormat format,
                                       VARIANT number, VARIANT font,
                                       VARIANT alignment, VARIANT border,
                                       VARIANT pattern, VARIANT width,
                                       VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeAutoOutline (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeBorderAround (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT lineStyle,
                                         enum ExcelEnum_XlBorderWeight weight,
                                         enum ExcelEnum_XlColorIndex colorIndex,
                                         VARIANT color, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeCalculate (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeCharacters (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT start,
                                       VARIANT length,
                                       ExcelObj_Characters *returnValue);

HRESULT CVIFUNC Excel_RangeCheckSpelling (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT customDictionary,
                                          VARIANT ignoreUppercase,
                                          VARIANT alwaysSuggest,
                                          VARIANT spellLang,
                                          VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeClear (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeClearContents (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeClearFormats (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeClearNotes (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeClearOutline (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeColumnDifferences (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              VARIANT comparison,
                                              ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeConsolidate (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT sources,
                                        VARIANT function, VARIANT topRow,
                                        VARIANT leftColumn, VARIANT createLinks,
                                        VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeCopy (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT destination, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeCopyFromRecordset (CAObjHandle objectHandle,
                                              ERRORINFO *errorInfo,
                                              LPUNKNOWN data, VARIANT maxRows,
                                              VARIANT maxColumns,
                                              long *returnValue);

HRESULT CVIFUNC Excel_RangeCopyPicture (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        enum ExcelEnum_XlPictureAppearance appearance,
                                        enum ExcelEnum_XlCopyPictureFormat format,
                                        VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeCreateNames (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT top,
                                        VARIANT left, VARIANT bottom,
                                        VARIANT right, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeCreatePublisher (CAObjHandle objectHandle,
                                            ERRORINFO *errorInfo,
                                            VARIANT edition,
                                            enum ExcelEnum_XlPictureAppearance appearance,
                                            VARIANT containsPICT,
                                            VARIANT containsBIFF,
                                            VARIANT containsRTF,
                                            VARIANT containsVALU,
                                            VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeCut (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT destination, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeDataSeries (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT rowcol,
                                       enum ExcelEnum_XlDataSeriesType type,
                                       enum ExcelEnum_XlDataSeriesDate date,
                                       VARIANT step, VARIANT stop, VARIANT trend,
                                       VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeGet_Default (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT rowIndex,
                                        VARIANT columnIndex,
                                        VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeSet_Default (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo, VARIANT rowIndex,
                                        VARIANT columnIndex, VARIANT newValue);

HRESULT CVIFUNC Excel_RangeDelete (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT shift,
                                   VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeDialogBox (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeEditionOptions (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           enum ExcelEnum_XlEditionType type,
                                           enum ExcelEnum_XlEditionOptionsOption option,
                                           VARIANT name, VARIANT reference,
                                           enum ExcelEnum_XlPictureAppearance appearance,
                                           enum ExcelEnum_XlPictureAppearance chartSize,
                                           VARIANT format, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeEnd (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                enum ExcelEnum_XlDirection direction,
                                ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeFillDown (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeFillLeft (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeFillRight (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeFillUp (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeFind (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT what, VARIANT after, VARIANT lookIn,
                                 VARIANT lookAt, VARIANT searchOrder,
                                 enum ExcelEnum_XlSearchDirection searchDirection,
                                 VARIANT matchCase, VARIANT matchByte,
                                 VARIANT searchFormat,
                                 ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeFindNext (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT after,
                                     ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeFindPrevious (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, VARIANT after,
                                         ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeFunctionWizard (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeGoalSeek (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT goal,
                                     ExcelObj_Range changingCell,
                                     VBOOL *returnValue);

HRESULT CVIFUNC Excel_RangeGroup (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT start, VARIANT end, VARIANT by,
                                  VARIANT periods, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeInsertIndent (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo, long insertAmount);

HRESULT CVIFUNC Excel_RangeInsert (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT shift,
                                   VARIANT copyOrigin, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeGetItem (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT rowIndex,
                                    VARIANT columnIndex, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeSetItem (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT rowIndex,
                                    VARIANT columnIndex, VARIANT newValue);

HRESULT CVIFUNC Excel_RangeJustify (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeListNames (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeMerge (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT across);

HRESULT CVIFUNC Excel_RangeUnMerge (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_RangeNavigateArrow (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT towardPrecedent,
                                          VARIANT arrowNumber,
                                          VARIANT linkNumber,
                                          VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeNoteText (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT text,
                                     VARIANT start, VARIANT length,
                                     char **returnValue);

HRESULT CVIFUNC Excel_RangeOffset (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT rowOffset,
                                   VARIANT columnOffset,
                                   ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeParse (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT parseLine, VARIANT destination,
                                  VARIANT *returnValue);

HRESULT CVIFUNC Excel_Range_PasteSpecial (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          enum ExcelEnum_XlPasteType paste,
                                          enum ExcelEnum_XlPasteSpecialOperation operation,
                                          VARIANT skipBlanks, VARIANT transpose,
                                          VARIANT *returnValue);

HRESULT CVIFUNC Excel_Range_PrintOut (CAObjHandle objectHandle,
                                      ERRORINFO *errorInfo, VARIANT from,
                                      VARIANT to, VARIANT copies,
                                      VARIANT preview, VARIANT activePrinter,
                                      VARIANT printToFile, VARIANT collate,
                                      VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangePrintPreview (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         VARIANT enableChanges,
                                         VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeRange (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT cell1, VARIANT cell2,
                                  ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeRemoveSubtotal (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeReplace (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT what,
                                    VARIANT replacement, VARIANT lookAt,
                                    VARIANT searchOrder, VARIANT matchCase,
                                    VARIANT matchByte, VARIANT searchFormat,
                                    VARIANT replaceFormat, VBOOL *returnValue);

HRESULT CVIFUNC Excel_RangeResize (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT rowSize,
                                   VARIANT columnSize,
                                   ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeRowDifferences (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo,
                                           VARIANT comparison,
                                           ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeRun (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                VARIANT arg1, VARIANT arg2, VARIANT arg3,
                                VARIANT arg4, VARIANT arg5, VARIANT arg6,
                                VARIANT arg7, VARIANT arg8, VARIANT arg9,
                                VARIANT arg10, VARIANT arg11, VARIANT arg12,
                                VARIANT arg13, VARIANT arg14, VARIANT arg15,
                                VARIANT arg16, VARIANT arg17, VARIANT arg18,
                                VARIANT arg19, VARIANT arg20, VARIANT arg21,
                                VARIANT arg22, VARIANT arg23, VARIANT arg24,
                                VARIANT arg25, VARIANT arg26, VARIANT arg27,
                                VARIANT arg28, VARIANT arg29, VARIANT arg30,
                                VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeSelect (CAObjHandle objectHandle,
                                   ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeShow (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeShowDependents (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT remove,
                                           VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeShowErrors (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo,
                                       VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeShowPrecedents (CAObjHandle objectHandle,
                                           ERRORINFO *errorInfo, VARIANT remove,
                                           VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeSort (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                 VARIANT key1, enum ExcelEnum_XlSortOrder order1,
                                 VARIANT key2, VARIANT type,
                                 enum ExcelEnum_XlSortOrder order2, VARIANT key3,
                                 enum ExcelEnum_XlSortOrder order3,
                                 enum ExcelEnum_XlYesNoGuess header,
                                 VARIANT orderCustom, VARIANT matchCase,
                                 enum ExcelEnum_XlSortOrientation orientation,
                                 enum ExcelEnum_XlSortMethod sortMethod,
                                 enum ExcelEnum_XlSortDataOption dataOption1,
                                 enum ExcelEnum_XlSortDataOption dataOption2,
                                 enum ExcelEnum_XlSortDataOption dataOption3,
                                 VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeSortSpecial (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        enum ExcelEnum_XlSortMethod sortMethod,
                                        VARIANT key1,
                                        enum ExcelEnum_XlSortOrder order1,
                                        VARIANT type, VARIANT key2,
                                        enum ExcelEnum_XlSortOrder order2,
                                        VARIANT key3,
                                        enum ExcelEnum_XlSortOrder order3,
                                        enum ExcelEnum_XlYesNoGuess header,
                                        VARIANT orderCustom, VARIANT matchCase,
                                        enum ExcelEnum_XlSortOrientation orientation,
                                        enum ExcelEnum_XlSortDataOption dataOption1,
                                        enum ExcelEnum_XlSortDataOption dataOption2,
                                        enum ExcelEnum_XlSortDataOption dataOption3,
                                        VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeSpecialCells (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         enum ExcelEnum_XlCellType type,
                                         VARIANT value,
                                         ExcelObj_Range *returnValue);

HRESULT CVIFUNC Excel_RangeSubscribeTo (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo,
                                        const char *edition,
                                        enum ExcelEnum_XlSubscribeToFormat format,
                                        VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeSubtotal (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, long groupBy,
                                     enum ExcelEnum_XlConsolidationFunction function,
                                     VARIANT totalList, VARIANT replace,
                                     VARIANT pageBreaks,
                                     enum ExcelEnum_XlSummaryRow summaryBelowData,
                                     VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeTable (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT rowInput, VARIANT columnInput,
                                  VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeTextToColumns (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo,
                                          VARIANT destination,
                                          enum ExcelEnum_XlTextParsingType dataType,
                                          enum ExcelEnum_XlTextQualifier textQualifier,
                                          VARIANT consecutiveDelimiter,
                                          VARIANT tab, VARIANT semicolon,
                                          VARIANT comma, VARIANT space,
                                          VARIANT other, VARIANT otherChar,
                                          VARIANT fieldInfo,
                                          VARIANT decimalSeparator,
                                          VARIANT thousandsSeparator,
                                          VARIANT trailingMinusNumbers,
                                          VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeUngroup (CAObjHandle objectHandle,
                                    ERRORINFO *errorInfo, VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeGetValue (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     VARIANT rangeValueDataType,
                                     VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeSetValue (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo,
                                     VARIANT rangeValueDataType,
                                     VARIANT newValue);

HRESULT CVIFUNC Excel_RangeAddComment (CAObjHandle objectHandle,
                                       ERRORINFO *errorInfo, VARIANT text,
                                       ExcelObj_Comment *returnValue);

HRESULT CVIFUNC Excel_RangeClearComments (CAObjHandle objectHandle,
                                          ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_RangeSetPhonetic (CAObjHandle objectHandle,
                                        ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_RangePrintOut (CAObjHandle objectHandle,
                                     ERRORINFO *errorInfo, VARIANT from,
                                     VARIANT to, VARIANT copies, VARIANT preview,
                                     VARIANT activePrinter, VARIANT printToFile,
                                     VARIANT collate, VARIANT prToFileName,
                                     VARIANT *returnValue);

HRESULT CVIFUNC Excel_RangeDirty (CAObjHandle objectHandle, ERRORINFO *errorInfo);

HRESULT CVIFUNC Excel_RangeSpeak (CAObjHandle objectHandle, ERRORINFO *errorInfo,
                                  VARIANT speakDirection, VARIANT speakFormulas);

HRESULT CVIFUNC Excel_RangePasteSpecial (CAObjHandle objectHandle,
                                         ERRORINFO *errorInfo,
                                         enum ExcelEnum_XlPasteType paste,
                                         enum ExcelEnum_XlPasteSpecialOperation operation,
                                         VARIANT skipBlanks, VARIANT transpose,
                                         VARIANT *returnValue);
#ifdef __cplusplus
    }
#endif
#endif /* _EXCEL_H */

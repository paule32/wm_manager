// --------------------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2019 Jens Kallup
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// --------------------------------------------------------------------------------
#include "win0003.h"

// to avoid overlaps ...
namespace kallup {
    namespace TWindowTUI {
        uchar TWindowApplication:: systemMenuIcon[] = "~\360~";
        uchar TWindowApplication::osystemMenuIcon[] = "~\360~";

        TVCodePageCallBack
        TWindowApplication::oldCPCallBack = nullptr;
        TWindowApplication * root_app     = nullptr;
        
        TWindowApplication::TWindowApplication(int argc, char **argv)
        : TProgInit(
            &TWindowApplication::initStatusLine,
            &TWindowApplication::initMenuBar,
            &TWindowApplication::initDeskTop)  {
            init_desktop();
        }
        TWindowApplication::TWindowApplication(void)
        : TProgInit(
            &TWindowApplication::initStatusLine,
            &TWindowApplication::initMenuBar,
            &TWindowApplication::initDeskTop)  {
            init_desktop();
        }

        void TWindowApplication::aboutDlgBox()
        {
            TDialog * aboutBox = new TDialog(TRect(0,0,42,13),"About");
            if (aboutBox) {
                aboutBox->options |= ofCentered;
                aboutBox->insert(
                    new TStaticText(TRect(4,2,40,9),
                        "\003Window Manager 1.0\n\n"
                        "\003Demo Version\n\n\n"
                        "\003Copyright (c) 2020\n\n\n"
                        "\003non-profit\n"
                        "\003KALLUP - Software"
                    )
                );
                aboutBox->insert(
                    new TButton(TRect(14,10,26,12), "~O~K", cmOK, bfDefault)
                );
                deskTop->execView(aboutBox);
                CLY_destroy(aboutBox);
            }
        }
        void TWindowApplication::TWindowApplication::init_desktop()
        {
            TRect r = getExtent();  // Create the clock view
            r.a.x = r.b.x - 9;
            r.b.y = r.a.y + 1;
            clock = new TClockView(r);
            insert(clock);
        }
        TStatusLine *
        TWindowApplication::initStatusLine(TRect r)
        {
            r.a.y = r.b.y - 1;
            return (new THintStatusLine(r,
            * new TStatusDef(0, 0xffff) +
                * new TStatusItem( "~F1~ Help", kbF1, cmHelp) +
                * new TStatusItem( "~F3~ Open", kbF3, cmOpen) +
                * new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit) +
                * new TStatusItem( 0, kbF10, cmMenu) +
                * new TStatusItem( 0, kbF5 , cmZoom) +
            * new TStatusDef(50, 0xffff) +
                * new TStatusItem( "Howdy", kbF1, cmHelp)
                )
            );
        }
        TMenuBar *
        TWindowApplication::initMenuBar(TRect r)
        {
            TSubMenu& sub1 =
                * new TSubMenu("~=~", kbAltSpace, hcNocontext) +
                    * new TMenuItem("~A~bout...", cmAboutCmd, kbNoKey, hcSAbout) +
                    newLine() +
                    * new TMenuItem("~P~uzzle"     , cmPuzzleCmd  , kbNoKey, hcSPuzzle) +
                    * new TMenuItem("Ca~l~endar"   , cmCalendarCmd, kbNoKey, hcSCalendar) +
                    * new TMenuItem("Ascii ~T~able", cmAsciiCmd   , kbNoKey, hcAsciiTable) +
                    * new TMenuItem("~C~alculatior", cmCalcCmd    , kbNoKey, hcCalculator) ;

            TSubMenu& sub2 =
                * new TSubMenu("~F~ile", 0, hcFile) +
                    * new TMenuItem("~N~ew"         , cmNewCmd ,   kbNoKey, hcFNew   ) +
                    * new TMenuItem("~O~pen..."     , cmOpenCmd,   kbF3   , hcFOpen  ) +
                    * new TMenuItem("~S~ave"        , cmSaveCmd,   kbF2   , hcFSave  ) +
                    * new TMenuItem("Save ~a~s..."  , cmSaveAsCmd, kbNoKey, hcFSaveAs) +
                    newLine() +
                    * new TMenuItem("S~h~ell"  , cmCallShell, kbNoKey , hcFDosShell) +
                    * new TMenuItem("E~x~it"   , cmQuit     , kbAltX  , hcFExit, "Alt-X" ) ;

            TSubMenu& sub3 =
                * new TSubMenu("~O~ptions", 0, hcOptions) +
                    * new TMenuItem("~M~ouse..."       , cmMouseCmd    , kbNoKey, hcOMouse) +
                    * new TMenuItem("~C~olors..."      , cmColorCmd    , kbNoKey, hcOColors) +
                    * new TMenuItem("~S~ave desktop"   , cmSaveCmd     , kbNoKey, hcOSaveDesktop) +
                    * new TMenuItem("~R~estore desktop", cmRestoreCmd  , kbNoKey, hcORestoreDesktop) +
                    * new TMenuItem("~T~est inputbox"  , cmTestInputBox, kbNoKey, hcNocontext);

            TSubMenu& sub4 =
                * new TSubMenu("~W~indows", 0, hcWindows) +
                    * new TMenuItem("~R~esize" , cmResize , kbCtrlF5, hcWSizeMove, "Ctrl-F5") +
                    * new TMenuItem("~Z~oom"   , cmZoom   , kbF5    , hcWZoom , "F5") +
                    * new TMenuItem("~N~ext"   , cmNext   , kbF6    , hcWNext , "F6") +
                    * new TMenuItem("~C~lose"  , cmClose  , kbAltF3 , hcWClose, "Alt-F3") +
                    * new TMenuItem("~T~ile"   , cmTile   , kbNoKey , hcWTile) +
                    * new TMenuItem("C~a~scade", cmCascade, kbNoKey , hcWCascade) ;

            r.b.y =  r.a.y + 1;
            return new TMenuBar(r, sub1 + sub2 + sub3 + sub4);
        }
        void
        TWindowApplication::puzzle()
        {
            TPuzzleWindow * puzz = (TPuzzleWindow *) validView(new TPuzzleWindow);
            if (puzz != 0) {
                puzz->helpCtx = hcPuzzle;
                deskTop->insert(puzz);
            }
        }
        void
        TWindowApplication::saveDesktop()
        {
            fpstream * f = new fpstream(dfn.c_str(),
                               CLY_IOSOut | CLY_IOSBin);
            if (f != 0) {
                TWindowApplication::storeDesktop(*f);
                if (!f) {
                    messageBox("Could not create setting file.", mfOKButton | mfError);
                    delete f;
                    ::remove(dfn.c_str());
                    return;
                }
            }
            delete f;
        }
        void
        TWindowApplication::retrieveDesktop()
        {
            FILE *fp = fopen(dfn.c_str(),"r");
            if (!fp) {
                messageBox("Could not find desktop file", mfOKButton | mfError);
                return;
            }
            fclose(fp);

            fpstream *f = new fpstream(dfn.c_str(),
                              CLY_IOSIn | CLY_IOSBin);
            if (!f) {
                messageBox("Could not find desktop file", mfOKButton | mfError);
                return;
            }

            TWindowApplication::loadDesktop(*f);
            if (!f) {
                messageBox("Error reading desktop file", mfOKButton | mfError);
            }   delete f;
        }

        static void closeView(TView *p, void *p1) {
            message(p, evCommand, cmClose, p1);
        }
        void
        TApplicationIDE::loadDesktop(fpstream &s)
        {
            TView *p;
            if (deskTop->valid(cmClose)) {
                deskTop->forEach(closeView,0);
                do {
                    s >> p;
                    deskTop->insertBefore(validView(p),
                    deskTop->last);
                } while (p != 0);
            }
        }

        static void writeView(TView *p, void *strm)
        {
            fpstream *s = (fpstream *) strm;
            if (p != TProgram::deskTop->last)
            *s << p;
        }

        void
        TWindowApplication::storeDesktop(fpstream &s)
        {
            deskTop->forEach(::writeView, &s);
            s << 0;
        }

        void
        TWindowApplication::cascade() {
            deskTop->cascade(
            deskTop->getExtent());
        }

        void
        TWindowApplication::tile() {
            deskTop->tile(
            deskTop->getExtent());
        }

        void
        TWindowApplication::changeDir()
        {
            TView *d = validView(new TChDirDialog(0, cmChangeDir));
            if (d != 0) {
                d->helpCtx = hcFCChDirDBox;
                deskTop->execView(d);
                CLY_destroy(d);
            }
        }

        ushort
        TWindowApplicationIDE::executeDialog(TDialog* pd, void* data)
        {
            ushort c = cmCancel;
            if (TProgram::application->validView(pd)) {
                if (data) {
                    pd->setData(data);
                    c = TProgram::deskTop->execView(pd);
                    if ((c != cmCancel) && (data))
                    pd->getData(data);
                    CLY_destroy(pd);
                }
            }
            return c;
        }

        void
        TWindowApplicationIDE::asciiTable()
        {
            TAsciiChart * chart = (TAsciiChart *) validView(new TAsciiChart);
            if (chart != 0) {
                chart->helpCtx = hcAsciiTable;
                deskTop->insert(chart);
                //deskTop->execView(chart);
            }   //CLY_destroy(chart);
        }

        void
        TWindowApplication::calculator()
        {
            TCalculator * calc = (TCalculator *) validView(new TCalculator);
            if (calc != 0) {
                calc->helpCtx = hcCalculator;
                deskTop->insert(calc);
                //deskTop->execView(calc);
            }   //CLY_destroy(calc);
        }

        void
        TWindowApplication::testInputBox()
        {
            char buffer[20];
            strcpy(buffer,"Initial value");
            if (inputBox(
                "Test for the inputBox",
                "Enter a number",
                buffer, 20) != cmCancel) {
                messageBox(mfInformation | mfOKButton, "Value entered: %s", buffer);
            }   else {
                messageBox("\x3""Input canceled", mfInformation | mfOKButton);
            }
        }

        bool
        TWindowApplication::isTileable(TView *p, void *)
        {
            if ((p->options & ofTileable) != 0)
            return true; else
            return false;
        }
        void
        TWindowApplication::cpCallBack(ushort *map)
        {
            TVCodePage::RemapString(systemMenuIcon, osystemMenuIcon, map);
            TCalendarView::upArrowChar   = TVCodePage::RemapChar(TCalendarView::oupArrowChar  ,map);
            TCalendarView::downArrowChar = TVCodePage::RemapChar(TCalendarView::odownArrowChar,map);

            if (oldCPCallBack)
                oldCPCallBack(map);
        }

        void
        TWindowApplication::openFile(char *name)
        {
            TFileDialog *d = (TFileDialog *) validView(
            new TFileDialog(name, "Open a File", "~N~ame", fdOpenButton, 100));

            if (d != 0 && deskTop->execView(d) != cmCancel) {
                char fileName[PATH_MAX];
                d->getFileName(fileName);
                d->helpCtx = hcFOFileOpenDBox;
                TView * w  = validView(new TFileWindow(fileName));
                if (w != 0) {
                    deskTop->insert(w);
                    deskTop->execView(d);
                }
            }
            CLY_destroy(d);
        }

        void
        TWindowApplication::calendar()
        {
            TCalendarWindow *win = (TCalendarWindow *) validView(new TCalendarWindow());
            if (!win) {
                deskTop->insert(win);
                deskTop->execView(win);
            }
            CLY_destroy(win);
        }

        void
        TWindowApplication::outOfMemory()
        {
            messageBox("Not enough memory available to complete operation.",
            mfError |
            mfOKButton);
        }

        void
        TWindowApplication::colors()
        {
            TColorGroup &group1 =
                *new TColorGroup("Desktop") +
                    *new TColorItem("Color",             1)+

                *new TColorGroup("Menus") +
                    *new TColorItem("Normal",            2)+
                    *new TColorItem("Disabled",          3)+
                    *new TColorItem("Shortcut",          4)+
                    *new TColorItem("Selected",          5)+
                    *new TColorItem("Selected disabled", 6)+
                    *new TColorItem("Shortcut selected", 7
            );

            TColorGroup &group2 =
                *new TColorGroup("Dialogs/Calc") +
                    *new TColorItem("Frame/background",  33)+
                    *new TColorItem("Frame icons",       34)+
                    *new TColorItem("Scroll bar page",   35)+
                    *new TColorItem("Scroll bar icons",  36)+
                    *new TColorItem("Static text",       37)+

                    *new TColorItem("Label normal",      38)+
                    *new TColorItem("Label selected",    39)+
                    *new TColorItem("Label shortcut",    40
                );

            TColorItem &item_coll1 =
                *new TColorItem("Button normal",     41)+
                *new TColorItem("Button default",    42)+
                *new TColorItem("Button selected",   43)+
                *new TColorItem("Button disabled",   44)+
                *new TColorItem("Button shortcut",   45)+
                *new TColorItem("Button shadow",     46)+
                *new TColorItem("Cluster normal",    47)+
                *new TColorItem("Cluster selected",  48)+
                *new TColorItem("Cluster shortcut",  49
                );

            TColorItem &item_coll2 =
                *new TColorItem("Input normal",      50)+
                *new TColorItem("Input selected",    51)+
                *new TColorItem("Input arrow",       52)+

                *new TColorItem("History button",    53)+
                *new TColorItem("History sides",     54)+
                *new TColorItem("History bar page",  55)+
                *new TColorItem("History bar icons", 56)+

                *new TColorItem("List normal",       57)+
                *new TColorItem("List focused",      58)+
                *new TColorItem("List selected",     59)+
                *new TColorItem("List divider",      60)+

                *new TColorItem("Information pane",  61
                );

             group2 = group2 + item_coll1 + item_coll2;

             TColorGroup &group3 =
                 *new TColorGroup("Viewer") +
                     *new TColorItem("Frame passive",      8)+
                     *new TColorItem("Frame active",       9)+
                     *new TColorItem("Frame icons",       10)+
                     *new TColorItem("Scroll bar page",   11)+
                     *new TColorItem("Scroll bar icons",  12)+
                     *new TColorItem("Text",              13)+
                 *new TColorGroup("Puzzle")+
                     *new TColorItem("Frame passive",      8)+
                     *new TColorItem("Frame active",       9)+
                     *new TColorItem("Frame icons",       10)+
                     *new TColorItem("Scroll bar page",   11)+
                     *new TColorItem("Scroll bar icons",  12)+
                     *new TColorItem("Normal text",       13)+
                     *new TColorItem("Highlighted text",  14
                 );


             TColorGroup &group4 =
                 *new TColorGroup("Calendar") +
                     *new TColorItem("Frame passive",     16)+
                     *new TColorItem("Frame active",      17)+
                     *new TColorItem("Frame icons",       18)+
                     *new TColorItem("Scroll bar page",   19)+
                     *new TColorItem("Scroll bar icons",  20)+
                     *new TColorItem("Normal text",       21)+
                     *new TColorItem("Current day",       22)+

                 *new TColorGroup("Ascii table") +
                     *new TColorItem("Frame passive",     24)+
                     *new TColorItem("Frame active",      25)+
                     *new TColorItem("Frame icons",       26)+
                     *new TColorItem("Scroll bar page",   27)+
                     *new TColorItem("Scroll bar icons",  28)+
                     *new TColorItem("Text",              29
                 );


            TColorGroup &group5 = group1 + group2 + group3 + group4;

            TPalette *temp_pal=new TPalette(getPalette());
            TColorDialog *c = new TColorDialog(temp_pal, &group5 );

            if (validView( c ) != 0)
            {
                c->helpCtx = hcOCColorsDBox;  // set context help constant
                c->setData(&getPalette());
                if (deskTop->execView( c ) != cmCancel) {
                    getPalette() = *(c->pal);
                    setScreenMode(TScreen::screenMode);
                }
                CLY_destroy(c);
            }
            delete temp_pal;
        }

        void
        TWindowApplication::handleEvent(TEvent& event)
        {
            TApplication::handleEvent(event);

            switch (event.what) {
            case evCommand:
            {
                switch (event.message.command)
                {
                case cmHelp:
                    if (!helpActive) {
                        if (nullptr != helpWindow)
                        CLY_destroy(helpWindow);
                        hnl:
                        helpWindow = new TMyHelpWindow(TRect(5,5,40,15));
                        if (helpWindow != 0) {
                            deskTop->insert(helpWindow);
                            //deskTop->execView(helpWindow);
                            helpActive = true;
                        }
                        else {
                            messageBox("help windpw could not be allocate.",
                            mfError | mfOKButton);
                            helpActive = false;
                            helpWindow = nullptr;
                            return;
                        }
                    }   else {
                        if (helpWindow != 0) {
                            //CLY_destroy(helpWindow);
                            helpWindow = nullptr;
                            helpActive = false;
                            goto hnl;
                        }
                    }
                    clearEvent(event);
                    break;
                case cmAboutCmd:
                    aboutDlgBox();
                    break;

                case cmAsciiCmd:
                    asciiTable();
                    break;

                case cmCalcCmd:
                    calculator();
                    break;

                case cmPuzzleCmd:
                    puzzle();
                    break;

                case cmCalendarCmd:
                    calendar();
                    break;

                case cmColorCmd:
                    colors();
                    break;

                case cmChDirCmd:
                    changeDir();
                    break;

                case cmTile:
                    tile();
                    break;

                case cmTestInputBox:
                    testInputBox();
                    break;

                case cmSaveCmd:
                    saveDesktop();
                    break;
                case cmRestoreCmd:
                    retrieveDesktop();
                    break;

                default:
                    return;
                }
                clearEvent(event);
            }
            break;
            }
        }

        #define cpAppColor \
               "\x71\x70\x78\x74\x20\x28\x24\x17\x1F\x1A\x31\x31\x1E\x71\x1F" \
            "\x37\x3F\x3A\x13\x13\x3E\x21\x3F\x70\x7F\x7A\x13\x13\x70\x7F\x7E" \
            "\x70\x7F\x7A\x13\x13\x70\x70\x7F\x7E\x20\x2B\x2F\x78\x2E\x70\x30" \
            "\x3F\x3E\x1F\x2F\x1A\x20\x72\x31\x31\x30\x2F\x3E\x31\x13\x38\x00" \
            "\x17\x1F\x1A\x71\x71\x1E\x17\x1F\x1E\x20\x2B\x2F\x78\x2E\x10\x30" \
            "\x3F\x3E\x70\x2F\x7A\x20\x12\x31\x31\x30\x2F\x3E\x31\x13\x38\x00" \
            "\x37\x3F\x3A\x13\x13\x3E\x30\x3F\x3E\x20\x2B\x2F\x78\x2E\x30\x70" \
            "\x7F\x7E\x1F\x2F\x1A\x20\x32\x31\x71\x70\x2F\x7E\x71\x13\x78\x00" \
            "\x37\x3F\x3A\x13\x13\x30\x3E\x1E"    // help colors

        #define cpAppBlackWhite \
               "\x70\x70\x78\x7F\x07\x07\x0F\x07\x0F\x07\x70\x70\x07\x70\x0F" \
            "\x07\x0F\x07\x70\x70\x07\x70\x0F\x70\x7F\x7F\x70\x07\x70\x07\x0F" \
            "\x70\x7F\x7F\x70\x07\x70\x70\x7F\x7F\x07\x0F\x0F\x78\x0F\x78\x07" \
            "\x0F\x0F\x0F\x70\x0F\x07\x70\x70\x70\x07\x70\x0F\x07\x07\x08\x00" \
            "\x07\x0F\x0F\x07\x70\x07\x07\x0F\x0F\x70\x78\x7F\x08\x7F\x08\x70" \
            "\x7F\x7F\x7F\x0F\x70\x70\x07\x70\x70\x70\x07\x7F\x70\x07\x78\x00" \
            "\x70\x7F\x7F\x70\x07\x70\x70\x7F\x7F\x07\x0F\x0F\x78\x0F\x78\x07" \
            "\x0F\x0F\x0F\x70\x0F\x07\x70\x70\x70\x07\x70\x0F\x07\x07\x08\x00" \
            "\x07\x0F\x07\x70\x70\x07\x0F\x70"    // help colors

        #define cpAppMonochrome \
               "\x70\x07\x07\x0F\x70\x70\x70\x07\x0F\x07\x70\x70\x07\x70\x00" \
            "\x07\x0F\x07\x70\x70\x07\x70\x00\x70\x70\x70\x07\x07\x70\x07\x00" \
            "\x70\x70\x70\x07\x07\x70\x70\x70\x0F\x07\x07\x0F\x70\x0F\x70\x07" \
            "\x0F\x0F\x07\x70\x07\x07\x70\x07\x07\x07\x70\x0F\x07\x07\x70\x00" \
            "\x70\x70\x70\x07\x07\x70\x70\x70\x0F\x07\x07\x0F\x70\x0F\x70\x07" \
            "\x0F\x0F\x07\x70\x07\x07\x70\x07\x07\x07\x70\x0F\x07\x07\x01\x00" \
            "\x70\x70\x70\x07\x07\x70\x70\x70\x0F\x07\x07\x0F\x70\x0F\x70\x07" \
            "\x0F\x0F\x07\x70\x07\x07\x70\x07\x07\x07\x70\x0F\x07\x07\x01\x00" \
            "\x07\x0F\x07\x70\x70\x07\x0F\x70"    // help colors

        TPalette&
        TWindowApplication::getPalette() const
        {
            static TPalette newcolor ( cpAppColor , sizeof( cpAppColor )-1 );
            static TPalette newblackwhite( cpAppBlackWhite , sizeof( cpAppBlackWhite )-1 );
            static TPalette newmonochrome( cpAppMonochrome , sizeof( cpAppMonochrome )-1 );
            static TPalette *palettes[] =
                {
                &newcolor,
                &newblackwhite,
                &newmonochrome
                };
            return *(palettes[appPalette]);

        }

        void
        TWindowApplication::getEvent(TEvent& event)
        {
            TApplication::getEvent(event);
        }

        void
        TWindowApplication::idle()
        {
            TProgram::idle();
            clock ->update();
        }
    }   // namespace: TWindowApplication
}       // namespace: TWindowTUI

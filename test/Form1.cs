using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NScci;
using Nc86ctl;

namespace test
{
    public partial class Form1 : Form
    {
        private NScci.NScci scci = null;
        private Nc86ctl.Nc86ctl c86 = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            scci = new NScci.NScci();

            int n = scci.NSoundInterfaceManager_.getInterfaceCount();
            if (n == 0)
            {
                scci.Dispose();
                scci = null;
            }
            else
            {
                NSoundInterface nsif = scci.NSoundInterfaceManager_.getInterface(0);
                int c = nsif.getSoundChipCount();
                NSoundChip nsc = nsif.getSoundChip(0);
                NSCCI_SOUND_CHIP_INFO nssci = nsc.getSoundChipInfo();
                string chipName = nssci.cSoundChipName;
            }


            c86 = new Nc86ctl.Nc86ctl();

            n = c86.getNumberOfChip();
            if (n == 0)
            {
                c86.deinitialize();
                c86 = null;
                //c86.Dispose();
                //c86 = null;
                return;
            }
            else
            {
                NIRealChip nirc = c86.getChipInterface(0);
                nirc.reset();

                NIGimic2 nig = nirc.QueryInterface();
                UInt16 aa = 0;
                UInt16 bb = 0;
                UInt16 cc = 0;
                UInt16 dd = 0;
                nig.getFWVer(ref aa, ref bb, ref cc, ref dd);
                Devinfo dv = nig.getMBInfo();
                ChipType tp = nig.getModuleType();
                Devinfo di = nig.getModuleInfo();
                byte vol = nig.getSSGVolume();
                ushort clock = nig.getPLLClock();
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (scci != null)
            {
                scci.Dispose();
                scci = null;
            }

            if (c86 != null)
            {
                c86.deinitialize();
                c86 = null;
            }

        }
    }
}

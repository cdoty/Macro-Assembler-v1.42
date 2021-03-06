/* asmlist.c */
/*****************************************************************************/
/* SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only                     */
/*                                                                           */
/* AS Port                                                                   */
/*                                                                           */
/* Generate Listing                                                          */
/*                                                                           */
/*****************************************************************************/

#include "stdinc.h"
#include <string.h>
#include "endian.h"
#include "strutil.h"
#include "asmdef.h"
#include "asmsub.h"
#include "asmif.h"
#include "asmcode.h"
#include "asmlist.h"

static unsigned SystemListLen8, SystemListLen16, SystemListLen32;

/*!------------------------------------------------------------------------
 * \fn     MakeList()
 * \brief  generate listing for one line, including generated code
 * ------------------------------------------------------------------------ */

void MakeList(const char *pSrcLine)
{
  String h, h2, Tmp;
  Word EffLen, Gran = Granularity();
  Boolean ThisDoLst;

  EffLen = CodeLen * Gran;

#if 0
  fprintf(stderr, "[%s] WasIF %u WasMACRO %u DoLst %u\n", OpPart.Str, WasIF, WasMACRO, DoLst);
#endif
  if (WasIF)
    ThisDoLst = !!(DoLst & eLstMacroExpIf);
  else if (WasMACRO)
    ThisDoLst = !!(DoLst & eLstMacroExpMacro);
  else
  {
    if (!IfAsm && (!(DoLst & eLstMacroExpIf)))
      ThisDoLst = False;
    else
      ThisDoLst = !!(DoLst & eLstMacroExpRest);
  }

  if ((!ListToNull) && (ThisDoLst) && ((ListMask & 1) != 0) && (!IFListMask()))
  {
    LargeWord ListPC;

    /* Zeilennummer / Programmzaehleradresse: */

    if (IncDepth == 0)
      as_snprintf(h, sizeof(h), "   ");
    else
    {
      as_snprintf(Tmp, sizeof(Tmp), IntegerFormat, IncDepth);
      as_snprintf(h, sizeof(h), "(%s)", Tmp);
    }
    if (ListMask & ListMask_LineNums)
    {
      as_snprintf(h2, sizeof(h2), Integ32Format, CurrLine);
      as_snprcatf(h, sizeof(h), "%5s/", h2);
    }
    ListPC = EProgCounter() - CodeLen;
    as_snprcatf(h, sizeof(h), "%8.*lllu %c ",
                ListRadixBase, ListPC, Retracted? 'R' : ':');

    /* Extrawurst in Listing ? */

    if (*ListLine)
    {
      strmaxcat(h, ListLine, sizeof(h));
      strmaxcat(h, Blanks(LISTLINESPACE - strlen(ListLine)), sizeof(h));
      strmaxcat(h, pSrcLine, sizeof(h));
      WrLstLine(h);
      *ListLine = '\0';
    }

    /* Code ausgeben */

    else
    {
      Word Index = 0, CurrListGran, SystemListLen;
      Boolean First = True;
      LargeInt ThisWord;
      int SumLen;

      /* Not enough code to display even on 16/32 bit word?
         Then start rightaway dumping bytes */

      if (EffLen < ActListGran)
      {
        CurrListGran = 1;
        SystemListLen = SystemListLen8;
      }
      else
      {
        CurrListGran = ActListGran;
        switch (CurrListGran)
        {
          case 4:
            SystemListLen = SystemListLen32;
            break;
          case 2:
            SystemListLen = SystemListLen16;
            break;
          default:
            SystemListLen = SystemListLen8;
        }
      }

      if (TurnWords && (Gran != ActListGran) && (1 == ActListGran))
        DreheCodes();
        
      do
      {
        /* If not the first code line, prepend blanks to fill up space below line number: */

        if (!First)
          as_snprintf(h, sizeof(h), "%*s%8.*lllu %c ",
                      (ListMask & ListMask_LineNums) ? 9 : 3, "",
                      ListRadixBase, ListPC, Retracted? 'R' : ':');

        SumLen = 0;
        do
        {
          /* We checked initially there is at least one full word,
             and we check after every word whether there is another
             full one: */

          if ((Index < EffLen) && !DontPrint)
          {
            switch (CurrListGran)
            {
              case 4:
                ThisWord = DAsmCode[Index >> 2];
                break;
              case 2:
                ThisWord = WAsmCode[Index >> 1];
                break;
              default:
                ThisWord = BAsmCode[Index];
            }
            as_snprcatf(h, sizeof(h), "%0*.*lllu ", (int)SystemListLen, (int)ListRadixBase, ThisWord);
          }
          else
            as_snprcatf(h, sizeof(h), "%*s", SystemListLen + 1, "");

          /* advance pointers & keep track of # of characters printed */

          ListPC += (Gran == CurrListGran) ? 1 : CurrListGran;
          Index += CurrListGran;
          SumLen += SystemListLen + 1;

          /* Less than one full word remaining? Then switch to dumping bytes. */

          if (Index + CurrListGran > EffLen)
          {
            CurrListGran = 1;
            SystemListLen = SystemListLen8;
          }
        }
        while (SumLen + SystemListLen + 1 < LISTLINESPACE);

        /* If first line, pad to max length and append source line */

        if (First)
          as_snprcatf(h, sizeof(h), "%*s%s", LISTLINESPACE - SumLen, "", pSrcLine);
        WrLstLine(h);
        First = False;
      }
      while ((Index < EffLen) && !DontPrint);

      if (TurnWords && (Gran != ActListGran) && (1 == ActListGran))
        DreheCodes();
    }
  }
}

/*!------------------------------------------------------------------------
 * \fn     asmlist_init(void)
 * \brief  setup stuff at program startup
 * ------------------------------------------------------------------------ */

void asmlist_init(void)
{
  String Dummy;

  SysString(Dummy, sizeof(Dummy), 0xff, ListRadixBase, 0, False, HexStartCharacter);
  SystemListLen8 = strlen(Dummy);
  SysString(Dummy, sizeof(Dummy), 0xffffu, ListRadixBase, 0, False, HexStartCharacter);
  SystemListLen16 = strlen(Dummy);
  SysString(Dummy, sizeof(Dummy), 0xfffffffful, ListRadixBase, 0, False, HexStartCharacter);
  SystemListLen32 = strlen(Dummy);
}

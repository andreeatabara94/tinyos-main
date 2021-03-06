configuration Msp432UsciSpiB0P {
  provides {
    interface Init;
    interface SpiPacket;
    interface SpiBlock;
    interface SpiByte;
    interface FastSpiByte;
    interface Msp432UsciError;
  }
  uses {
    interface Msp432UsciConfigure;
    interface HplMsp432Gpio as SIMO;
    interface HplMsp432Gpio as SOMI;
    interface HplMsp432Gpio as CLK;
    interface Panic;
    interface Platform;
 }
}
implementation {
  components     Msp432UsciB0P    as UsciP;
  components new Msp432UsciSpiP() as SpiP;

  SpiP.Usci             -> UsciP;
  SpiP.Interrupt        -> UsciP;

  SIMO                  =  SpiP.SIMO;
  SOMI                  =  SpiP.SOMI;
  CLK                   =  SpiP.CLK;

  Panic                 =  SpiP;
  Platform              =  SpiP;

  Init                  =  SpiP;
  Msp432UsciConfigure   =  SpiP;

  SpiPacket             =  SpiP;
  SpiBlock              =  SpiP;
  SpiByte               =  SpiP;
  FastSpiByte           =  SpiP;
  Msp432UsciError       =  SpiP;
}

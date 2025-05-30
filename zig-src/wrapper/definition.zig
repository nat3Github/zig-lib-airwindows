pub const replace = "Acceleration";
pub const plugin_base_path = "plugins/WinVST/";
pub const complete_index: []const []const u8 = &get_complete_index();

fn get_complete_index() [@typeInfo(index_imports).@"struct".decls.len][]const u8 {
    const decls = @typeInfo(index_imports).@"struct".decls;
    var x: [decls.len][]const u8 = undefined;
    inline for (&x, decls) |*d, decl| {
        d.* = decl.name;
    }
    return x;
}

pub const index_imports = struct {
    pub const Acceleration = @import("Acceleration");
    pub const Acceleration2 = @import("Acceleration2");
    pub const ADClip7 = @import("ADClip7");
    pub const ADClip8 = @import("ADClip8");
    pub const ADT = @import("ADT");
    pub const Air = @import("Air");
    pub const Air2 = @import("Air2");
    pub const Air3 = @import("Air3");
    pub const Air4 = @import("Air4");
    pub const AngleEQ = @import("AngleEQ");
    pub const AngleFilter = @import("AngleFilter");
    pub const Apicolypse = @import("Apicolypse");
    pub const AQuickVoiceClip = @import("AQuickVoiceClip");
    pub const AtmosphereBuss = @import("AtmosphereBuss");
    pub const AtmosphereChannel = @import("AtmosphereChannel");
    pub const Aura = @import("Aura");
    pub const AutoPan = @import("AutoPan");
    pub const Average = @import("Average");
    pub const AverMatrix = @import("AverMatrix");
    pub const Balanced = @import("Balanced");
    pub const BassAmp = @import("BassAmp");
    pub const BassDrive = @import("BassDrive");
    pub const BassKit = @import("BassKit");
    pub const Baxandall = @import("Baxandall");
    pub const Baxandall2 = @import("Baxandall2");
    pub const Baxandall3 = @import("Baxandall3");
    pub const Beam = @import("Beam");
    pub const BezEQ = @import("BezEQ");
    pub const BeziComp = @import("BeziComp");
    pub const BigAmp = @import("BigAmp");
    pub const Biquad = @import("Biquad");
    pub const Biquad2 = @import("Biquad2");
    pub const BiquadDouble = @import("BiquadDouble");
    pub const BiquadHiLo = @import("BiquadHiLo");
    pub const BiquadNonLin = @import("BiquadNonLin");
    pub const BiquadOneHalf = @import("BiquadOneHalf");
    pub const BiquadPlus = @import("BiquadPlus");
    pub const BiquadStack = @import("BiquadStack");
    pub const BiquadTriple = @import("BiquadTriple");
    pub const Bite = @import("Bite");
    pub const BitGlitter = @import("BitGlitter");
    pub const BitShiftGain = @import("BitShiftGain");
    pub const BitShiftPan = @import("BitShiftPan");
    pub const BlockParty = @import("BlockParty");
    pub const BrassRider = @import("BrassRider");
    pub const BrightAmbience = @import("BrightAmbience");
    pub const BrightAmbience2 = @import("BrightAmbience2");
    pub const BrightAmbience3 = @import("BrightAmbience3");
    pub const BuildATPDF = @import("BuildATPDF");
    pub const BussColors4 = @import("BussColors4");
    pub const ButterComp = @import("ButterComp");
    pub const ButterComp2 = @import("ButterComp2");
    pub const C5RawBuss = @import("C5RawBuss");
    pub const C5RawChannel = @import("C5RawChannel");
    pub const Cabs = @import("Cabs");
    pub const Calibre = @import("Calibre");
    pub const Cans = @import("Cans");
    pub const CansAW = @import("CansAW");
    pub const Capacitor = @import("Capacitor");
    pub const Capacitor2 = @import("Capacitor2");
    pub const Chamber = @import("Chamber");
    pub const Chamber2 = @import("Chamber2");
    pub const Channel4 = @import("Channel4");
    pub const Channel5 = @import("Channel5");
    pub const Channel6 = @import("Channel6");
    pub const Channel7 = @import("Channel7");
    pub const Channel8 = @import("Channel8");
    pub const Channel9 = @import("Channel9");
    pub const ChimeyGuitar = @import("ChimeyGuitar");
    pub const Chorus = @import("Chorus");
    pub const ChorusEnsemble = @import("ChorusEnsemble");
    pub const ChromeOxide = @import("ChromeOxide");
    pub const Cider = @import("Cider");
    pub const ClearCoat = @import("ClearCoat");
    pub const ClipOnly = @import("ClipOnly");
    pub const ClipOnly2 = @import("ClipOnly2");
    pub const ClipSoftly = @import("ClipSoftly");
    pub const CloudCoat = @import("CloudCoat");
    pub const Coils = @import("Coils");
    pub const Coils2 = @import("Coils2");
    pub const Cojones = @import("Cojones");
    pub const Compresaturator = @import("Compresaturator");
    pub const Console0Buss = @import("Console0Buss");
    pub const Console0Channel = @import("Console0Channel");
    pub const Console4Buss = @import("Console4Buss");
    pub const Console4Channel = @import("Console4Channel");
    pub const Console5Buss = @import("Console5Buss");
    pub const Console5Channel = @import("Console5Channel");
    pub const Console5DarkCh = @import("Console5DarkCh");
    pub const Console6Buss = @import("Console6Buss");
    pub const Console6Channel = @import("Console6Channel");
    pub const Console7Buss = @import("Console7Buss");
    pub const Console7Cascade = @import("Console7Cascade");
    pub const Console7Channel = @import("Console7Channel");
    pub const Console7Crunch = @import("Console7Crunch");
    pub const Console8BussHype = @import("Console8BussHype");
    pub const Console8BussIn = @import("Console8BussIn");
    pub const Console8BussOut = @import("Console8BussOut");
    pub const Console8ChannelHype = @import("Console8ChannelHype");
    pub const Console8ChannelIn = @import("Console8ChannelIn");
    pub const Console8ChannelOut = @import("Console8ChannelOut");
    pub const Console8LiteBuss = @import("Console8LiteBuss");
    pub const Console8LiteChannel = @import("Console8LiteChannel");
    pub const Console8SubHype = @import("Console8SubHype");
    pub const Console8SubIn = @import("Console8SubIn");
    pub const Console8SubOut = @import("Console8SubOut");
    pub const Console9Buss = @import("Console9Buss");
    pub const Console9Channel = @import("Console9Channel");
    pub const ConsoleLABuss = @import("ConsoleLABuss");
    pub const ConsoleLAChannel = @import("ConsoleLAChannel");
    pub const ConsoleMCBuss = @import("ConsoleMCBuss");
    pub const ConsoleMCChannel = @import("ConsoleMCChannel");
    pub const ConsoleMDBuss = @import("ConsoleMDBuss");
    pub const ConsoleMDChannel = @import("ConsoleMDChannel");
    pub const ConsoleXBuss = @import("ConsoleXBuss");
    pub const ConsoleXChannel = @import("ConsoleXChannel");
    pub const ConsoleXPre = @import("ConsoleXPre");
    pub const ContentHideD = @import("ContentHideD");
    pub const CreamCoat = @import("CreamCoat");
    pub const Creature = @import("Creature");
    pub const CrickBass = @import("CrickBass");
    pub const CrunchCoat = @import("CrunchCoat");
    pub const CrunchyGrooveWear = @import("CrunchyGrooveWear");
    pub const Crystal = @import("Crystal");
    pub const CStrip = @import("CStrip");
    pub const CStrip2 = @import("CStrip2");
    pub const curve = @import("curve");
    pub const Dark = @import("Dark");
    pub const DarkNoise = @import("DarkNoise");
    pub const DCVoltage = @import("DCVoltage");
    pub const DeBess = @import("DeBess");
    pub const Deckwrecka = @import("Deckwrecka");
    pub const DeCrackle = @import("DeCrackle");
    pub const DeEss = @import("DeEss");
    pub const DeHiss = @import("DeHiss");
    pub const Density = @import("Density");
    pub const Density2 = @import("Density2");
    pub const DeRez = @import("DeRez");
    pub const DeRez2 = @import("DeRez2");
    pub const DeRez3 = @import("DeRez3");
    pub const Desk = @import("Desk");
    pub const Desk4 = @import("Desk4");
    pub const DigitalBlack = @import("DigitalBlack");
    pub const Dirt = @import("Dirt");
    pub const Discontinuity = @import("Discontinuity");
    pub const Disintegrate = @import("Disintegrate");
    pub const Distance = @import("Distance");
    pub const Distance2 = @import("Distance2");
    pub const Distance3 = @import("Distance3");
    pub const Distortion = @import("Distortion");
    pub const Ditherbox = @import("Ditherbox");
    pub const DitherFloat = @import("DitherFloat");
    pub const DitherMeDiskers = @import("DitherMeDiskers");
    pub const DitherMeTimbers = @import("DitherMeTimbers");
    pub const Doublelay = @import("Doublelay");
    pub const DoublePaul = @import("DoublePaul");
    pub const Drive = @import("Drive");
    pub const DrumSlam = @import("DrumSlam");
    pub const DubCenter = @import("DubCenter");
    pub const Dubly = @import("Dubly");
    pub const Dubly2 = @import("Dubly2");
    pub const Dubly3 = @import("Dubly3");
    pub const DubPlate = @import("DubPlate");
    pub const DubPlate2 = @import("DubPlate2");
    pub const DubSub = @import("DubSub");
    pub const DubSub2 = @import("DubSub2");
    pub const DustBunny = @import("DustBunny");
    pub const Dynamics = @import("Dynamics");
    pub const Dyno = @import("Dyno");
    pub const Edge = @import("Edge");
    pub const EdIsDim = @import("EdIsDim");
    pub const Elation = @import("Elation");
    pub const ElectroHat = @import("ElectroHat");
    pub const Elliptical = @import("Elliptical");
    pub const Energy = @import("Energy");
    pub const Energy2 = @import("Energy2");
    pub const Ensemble = @import("Ensemble");
    pub const EQ = @import("EQ");
    pub const EveryConsole = @import("EveryConsole");
    pub const EverySlew = @import("EverySlew");
    pub const EveryTrim = @import("EveryTrim");
    pub const Exciter = @import("Exciter");
    pub const Facet = @import("Facet");
    pub const FathomFive = @import("FathomFive");
    pub const FinalClip = @import("FinalClip");
    pub const FireAmp = @import("FireAmp");
    pub const Flipity = @import("Flipity");
    pub const Floor = @import("Floor");
    pub const Flutter = @import("Flutter");
    pub const Flutter2 = @import("Flutter2");
    pub const Focus = @import("Focus");
    pub const Fracture = @import("Fracture");
    pub const Fracture2 = @import("Fracture2");
    pub const FromTape = @import("FromTape");
    pub const Galactic = @import("Galactic");
    pub const Galactic2 = @import("Galactic2");
    pub const Galactic3 = @import("Galactic3");
    pub const GalacticVibe = @import("GalacticVibe");
    pub const Gatelope = @import("Gatelope");
    pub const GlitchShifter = @import("GlitchShifter");
    pub const GoldenSlew = @import("GoldenSlew");
    pub const Golem = @import("Golem");
    pub const GrindAmp = @import("GrindAmp");
    pub const Gringer = @import("Gringer");
    pub const GrooveWear = @import("GrooveWear");
    pub const GuitarConditioner = @import("GuitarConditioner");
    pub const HardVacuum = @import("HardVacuum");
    pub const Hermepass = @import("Hermepass");
    pub const HermeTrim = @import("HermeTrim");
    pub const HighGlossDither = @import("HighGlossDither");
    pub const HighImpact = @import("HighImpact");
    pub const Highpass = @import("Highpass");
    pub const Highpass2 = @import("Highpass2");
    pub const Holt = @import("Holt");
    pub const Holt2 = @import("Holt2");
    pub const Hombre = @import("Hombre");
    pub const Huge = @import("Huge");
    pub const Hull = @import("Hull");
    pub const Hull2 = @import("Hull2");
    pub const Hype = @import("Hype");
    pub const Hypersoft = @import("Hypersoft");
    pub const Hypersonic = @import("Hypersonic");
    pub const HypersonX = @import("HypersonX");
    pub const Infinity = @import("Infinity");
    pub const Infinity2 = @import("Infinity2");
    pub const Inflamer = @import("Inflamer");
    pub const Infrasonic = @import("Infrasonic");
    pub const Interstage = @import("Interstage");
    pub const IronOxide5 = @import("IronOxide5");
    pub const IronOxideClassic = @import("IronOxideClassic");
    pub const IronOxideClassic2 = @import("IronOxideClassic2");
    pub const Isolator = @import("Isolator");
    pub const Isolator2 = @import("Isolator2");
    pub const Isolator3 = @import("Isolator3");
    pub const Kalman = @import("Kalman");
    pub const kCathedral = @import("kCathedral");
    pub const kCathedral2 = @import("kCathedral2");
    pub const kCathedral3 = @import("kCathedral3");
    pub const kChamberAR = @import("kChamberAR");
    pub const kCosmos = @import("kCosmos");
    pub const kGuitarHall = @import("kGuitarHall");
    pub const kPlate140 = @import("kPlate140");
    pub const kPlate240 = @import("kPlate240");
    pub const kPlateA = @import("kPlateA");
    pub const kPlateB = @import("kPlateB");
    pub const kPlateC = @import("kPlateC");
    pub const kPlateD = @import("kPlateD");
    pub const LeadAmp = @import("LeadAmp");
    pub const LeftoMono = @import("LeftoMono");
    pub const LilAmp = @import("LilAmp");
    pub const Logical4 = @import("Logical4");
    pub const Loud = @import("Loud");
    pub const Lowpass = @import("Lowpass");
    pub const Lowpass2 = @import("Lowpass2");
    pub const LRConvolve = @import("LRConvolve");
    pub const LRConvolve2 = @import("LRConvolve2");
    pub const LRConvolve3 = @import("LRConvolve3");
    pub const LRFlipTimer = @import("LRFlipTimer");
    pub const Luxor = @import("Luxor");
    pub const MackEQ = @import("MackEQ");
    pub const Mackity = @import("Mackity");
    pub const Mastering = @import("Mastering");
    pub const Mastering2 = @import("Mastering2");
    pub const MatrixVerb = @import("MatrixVerb");
    pub const Melt = @import("Melt");
    pub const MidAmp = @import("MidAmp");
    pub const MidSide = @import("MidSide");
    pub const Mojo = @import("Mojo");
    pub const Monitoring = @import("Monitoring");
    pub const Monitoring2 = @import("Monitoring2");
    pub const Monitoring3 = @import("Monitoring3");
    pub const MoNoam = @import("MoNoam");
    pub const MSFlipTimer = @import("MSFlipTimer");
    pub const MultiBandDistortion = @import("MultiBandDistortion");
    pub const MV = @import("MV");
    pub const MV2 = @import("MV2");
    pub const NaturalizeDither = @import("NaturalizeDither");
    pub const NCSeventeen = @import("NCSeventeen");
    pub const Neverland = @import("Neverland");
    pub const Nikola = @import("Nikola");
    pub const NodeDither = @import("NodeDither");
    pub const Noise = @import("Noise");
    pub const NonlinearSpace = @import("NonlinearSpace");
    pub const NotJustAnotherCD = @import("NotJustAnotherCD");
    pub const NotJustAnotherDither = @import("NotJustAnotherDither");
    pub const OneCornerClip = @import("OneCornerClip");
    pub const OrbitKick = @import("OrbitKick");
    pub const Overheads = @import("Overheads");
    pub const Pafnuty = @import("Pafnuty");
    pub const Pafnuty2 = @import("Pafnuty2");
    pub const Parametric = @import("Parametric");
    pub const PaulDither = @import("PaulDither");
    pub const PaulWide = @import("PaulWide");
    pub const PDBuss = @import("PDBuss");
    pub const PDChannel = @import("PDChannel");
    pub const PeaksOnly = @import("PeaksOnly");
    pub const Pear = @import("Pear");
    pub const Pear2 = @import("Pear2");
    pub const PhaseNudge = @import("PhaseNudge");
    pub const PitchDelay = @import("PitchDelay");
    pub const PitchNasty = @import("PitchNasty");
    pub const PlatinumSlew = @import("PlatinumSlew");
    pub const PocketVerbs = @import("PocketVerbs");
    pub const Pockey = @import("Pockey");
    pub const Pockey2 = @import("Pockey2");
    pub const Podcast = @import("Podcast");
    pub const PodcastDeluxe = @import("PodcastDeluxe");
    pub const Point = @import("Point");
    pub const PointyGuitar = @import("PointyGuitar");
    pub const Pop = @import("Pop");
    pub const Pop2 = @import("Pop2");
    pub const Pop3 = @import("Pop3");
    pub const PowerSag = @import("PowerSag");
    pub const PowerSag2 = @import("PowerSag2");
    pub const Precious = @import("Precious");
    pub const Preponderant = @import("Preponderant");
    pub const Pressure4 = @import("Pressure4");
    pub const Pressure5 = @import("Pressure5");
    pub const PrimeFIR = @import("PrimeFIR");
    pub const PunchyGuitar = @import("PunchyGuitar");
    pub const PurestAir = @import("PurestAir");
    pub const PurestConsole2Buss = @import("PurestConsole2Buss");
    pub const PurestConsole2Channel = @import("PurestConsole2Channel");
    pub const PurestConsole3Buss = @import("PurestConsole3Buss");
    pub const PurestConsole3Channel = @import("PurestConsole3Channel");
    pub const PurestConsoleBuss = @import("PurestConsoleBuss");
    pub const PurestConsoleChannel = @import("PurestConsoleChannel");
    pub const PurestDrive = @import("PurestDrive");
    pub const PurestEcho = @import("PurestEcho");
    pub const PurestFade = @import("PurestFade");
    pub const PurestGain = @import("PurestGain");
    pub const PurestSquish = @import("PurestSquish");
    pub const PurestWarm = @import("PurestWarm");
    pub const PurestWarm2 = @import("PurestWarm2");
    pub const Pyewacket = @import("Pyewacket");
    pub const RawGlitters = @import("RawGlitters");
    pub const RawTimbers = @import("RawTimbers");
    pub const Recurve = @import("Recurve");
    pub const Remap = @import("Remap");
    pub const ResEQ = @import("ResEQ");
    pub const ResEQ2 = @import("ResEQ2");
    pub const Reverb = @import("Reverb");
    pub const Righteous4 = @import("Righteous4");
    pub const RightoMono = @import("RightoMono");
    pub const RingModulator = @import("RingModulator");
    pub const SampleDelay = @import("SampleDelay");
    pub const Shape = @import("Shape");
    pub const ShortBuss = @import("ShortBuss");
    pub const SideDull = @import("SideDull");
    pub const Sidepass = @import("Sidepass");
    pub const Silhouette = @import("Silhouette");
    pub const Sinew = @import("Sinew");
    pub const SingleEndedTriode = @import("SingleEndedTriode");
    pub const Slew = @import("Slew");
    pub const Slew2 = @import("Slew2");
    pub const Slew3 = @import("Slew3");
    pub const SlewOnly = @import("SlewOnly");
    pub const SlewSonic = @import("SlewSonic");
    pub const Smooth = @import("Smooth");
    pub const SmoothEQ = @import("SmoothEQ");
    pub const SoftClock = @import("SoftClock");
    pub const SoftGate = @import("SoftGate");
    pub const SpatializeDither = @import("SpatializeDither");
    pub const Spiral = @import("Spiral");
    pub const Spiral2 = @import("Spiral2");
    pub const SquareRoot = @import("SquareRoot");
    pub const Srsly = @import("Srsly");
    pub const Srsly2 = @import("Srsly2");
    pub const Srsly3 = @import("Srsly3");
    pub const StarChild = @import("StarChild");
    pub const StarChild2 = @import("StarChild2");
    pub const StereoChorus = @import("StereoChorus");
    pub const StereoDoubler = @import("StereoDoubler");
    pub const StereoEnsemble = @import("StereoEnsemble");
    pub const StereoFX = @import("StereoFX");
    pub const Stonefire = @import("Stonefire");
    pub const StoneFireComp = @import("StoneFireComp");
    pub const StudioTan = @import("StudioTan");
    pub const SubsOnly = @import("SubsOnly");
    pub const SubTight = @import("SubTight");
    pub const Surge = @import("Surge");
    pub const SurgeTide = @import("SurgeTide");
    pub const Sweeten = @import("Sweeten");
    pub const SweetWide = @import("SweetWide");
    pub const Swell = @import("Swell");
    pub const Tape = @import("Tape");
    pub const TapeBias = @import("TapeBias");
    pub const TapeDelay = @import("TapeDelay");
    pub const TapeDelay2 = @import("TapeDelay2");
    pub const TapeDither = @import("TapeDither");
    pub const TapeDust = @import("TapeDust");
    pub const TapeFat = @import("TapeFat");
    pub const Texturize = @import("Texturize");
    pub const TexturizeMS = @import("TexturizeMS");
    pub const Thunder = @import("Thunder");
    pub const ToneSlant = @import("ToneSlant");
    pub const ToTape5 = @import("ToTape5");
    pub const ToTape6 = @import("ToTape6");
    pub const ToTape7 = @import("ToTape7");
    pub const ToTape8 = @import("ToTape8");
    pub const ToVinyl4 = @import("ToVinyl4");
    pub const TPDFDither = @import("TPDFDither");
    pub const TPDFWide = @import("TPDFWide");
    pub const TransDesk = @import("TransDesk");
    pub const Tremolo = @import("Tremolo");
    pub const TremoSquare = @import("TremoSquare");
    pub const Trianglizer = @import("Trianglizer");
    pub const TripleSpread = @import("TripleSpread");
    pub const Tube = @import("Tube");
    pub const Tube2 = @import("Tube2");
    pub const TubeDesk = @import("TubeDesk");
    pub const uLawDecode = @import("uLawDecode");
    pub const uLawEncode = @import("uLawEncode");
    pub const Ultrasonic = @import("Ultrasonic");
    pub const UltrasonicLite = @import("UltrasonicLite");
    pub const UltrasonicMed = @import("UltrasonicMed");
    pub const UltrasonX = @import("UltrasonX");
    pub const UnBox = @import("UnBox");
    pub const VariMu = @import("VariMu");
    pub const Verbity = @import("Verbity");
    pub const Verbity2 = @import("Verbity2");
    pub const Vibrato = @import("Vibrato");
    pub const VinylDither = @import("VinylDither");
    pub const VoiceOfTheStarship = @import("VoiceOfTheStarship");
    pub const VoiceTrick = @import("VoiceTrick");
    pub const Weight = @import("Weight");
    pub const Wider = @import("Wider");
    pub const Wolfbot = @import("Wolfbot");
    pub const XBandpass = @import("XBandpass");
    pub const XHighpass = @import("XHighpass");
    pub const XLowpass = @import("XLowpass");
    pub const XNotch = @import("XNotch");
    pub const XRegion = @import("XRegion");
    pub const YBandpass = @import("YBandpass");
    pub const YHighpass = @import("YHighpass");
    pub const YLowpass = @import("YLowpass");
    pub const YNotBandpass = @import("YNotBandpass");
    pub const YNotch = @import("YNotch");
    pub const YNotHighpass = @import("YNotHighpass");
    pub const YNotLowpass = @import("YNotLowpass");
    pub const YNotNotch = @import("YNotNotch");
    pub const ZBandpass = @import("ZBandpass");
    pub const ZBandpass2 = @import("ZBandpass2");
    pub const ZHighpass = @import("ZHighpass");
    pub const ZHighpass2 = @import("ZHighpass2");
    pub const ZLowpass = @import("ZLowpass");
    pub const ZLowpass2 = @import("ZLowpass2");
    pub const ZNotch = @import("ZNotch");
    pub const ZNotch2 = @import("ZNotch2");
    pub const Zoom = @import("Zoom");
    pub const ZOutputStage = @import("ZOutputStage");
    pub const ZRegion = @import("ZRegion");
    pub const ZRegion2 = @import("ZRegion2");
};

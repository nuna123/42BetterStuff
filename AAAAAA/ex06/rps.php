<?php

$a = readline('Choose rock, paper or scissors: ');
$user_choice = 0;
$comp_choice = rand(1,3);

// 1 == ROCK
// 2 == PAPER
// 3 == SCISSORS

if ($a == 'rock') {
	if ($comp_choice == 1){echo "TIE! the computer chose Rock.\n";}
	if ($comp_choice == 2){echo "Sorry, you lost. the computer chose Paper.\n";}
	if ($comp_choice == 3){echo "YOU WON! the computer chose Scissors.\n";}
	exit (0);
} elseif ($a == 'paper') {
	if ($comp_choice == 1){echo "YOU WON! the computer chose Rock.\n";}
	if ($comp_choice == 2){echo "TIE! the computer chose Paper.\n";}
	if ($comp_choice == 3){echo "Sorry, you lost. the computer chose Scissors.\n";}
	exit (0);
}
elseif ($a == 'scissors') {
	if ($comp_choice == 1){echo "Sorry, you lost. the computer chose Rock.\n";}
	if ($comp_choice == 2){echo "YOU WON! the computer chose Paper.\n";}
	if ($comp_choice == 3){echo "TIE! the computer chose Scissors.\n";}
	exit (0);
}
echo "Ew what is that.\n";
exit(1);


?>
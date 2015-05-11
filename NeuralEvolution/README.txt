 ______     ______     ______     _____        __    __     ______    
/\  == \   /\  ___\   /\  __ \   /\  __-.     /\ "-./  \   /\  ___\   
\ \  __<   \ \  __\   \ \  __ \  \ \ \/\ \    \ \ \-./\ \  \ \  __\   
 \ \_\ \_\  \ \_____\  \ \_\ \_\  \ \____-     \ \_\ \ \_\  \ \_____\ 
  \/_/ /_/   \/_____/   \/_/\/_/   \/____/      \/_/  \/_/   \/_____/ 

Project Name:	Evolutionary Artificial Neural Networks
Created by: 	Sawyer Bowman '15, David Needell '15, Phoebe Bumsted ’17, Ryan Barrett ’17
Email:			Sawyer:	sbowman@bowdoin.edu
			David:	dneedell@bowdoin.edu
			Phoebe:	pbumsted@bowdoin.edu
			Ryan:	rbarrett@bowdoin.edu

Date Created: 	April, 2015
Last Modified: 	May, 2015 
Version:		1.0
Language: 		C++

---------------------------------------------------------------------

DESCRIPTION:
This program attempts to recognize the subject of an image using an artificial
neural network and 

HOW TO RUN:
The user must pass the following parameters as command line arguments.

//ARGUMENTS
training file (string)			ex. ../lists/straighteven_train.list.txt
testing file  (string)			ex. ../lists/straighteven_test.list.txt
learning rate (double)			ex. 0.3
selection     (string)			ex. bs (boltzmann)
crossover     (string)			ex. 1c (one-point crossover)
crossover probability (double)		ex. 0.5
mutation probability  (double)		ex. 0.01
generations   (int)			ex. 5
population size (int)			ex. 8


It’s constants.h, modify EVOLVE to be false or true depending on whether you want
to test a fully connected ANN or a EANN, respectfully.

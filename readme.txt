@author
Barak Golan




note about game exception:
the board will accpet 0-4 ghost
if there are more then 4 ,the board will ignore fifth and aboves
the board screen cannot be more then 80 width * 25 height
the game will ingore the char above that


the game throw exception in this cases:
number of pacman != 1
number of legend != 1
error if not enough save for legend(overflow in the width or in the height)
error if working workinh directory not have a least 1 '.screen' file
error on failed to open screen file(exist but cannot be open)
error on failed to open step file in (game mode != simple)
error on failed to open result file in (game mode == save or game mode ==load silent)
error if board screen not exist or not '.screen'
error if missing steps in step file to success end the screen
error if steps include invaild direction for the creatures
error on invaild command argument or more then 2 argument command
error if board faild in test



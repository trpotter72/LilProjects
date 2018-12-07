import time, logging, os #Imports time and logging modules. Time creates pauses while logging outputs data about the code.

logger = logging.getLogger() #Setting up the logger
handler = logging.StreamHandler()
formatter = logging.Formatter('%(asctime)s %(name)-12s %(levelname)-8s %(message)s')
handler.setFormatter(formatter)
logger.addHandler(handler)
logger.setLevel(logging.DEBUG)

#To enable the logger, comment the line below
logging.disable(logging.CRITICAL)

lose =   """

      __   __            _                _
      \ \ / /           | |              | |
       \ V /___  _   _  | | ___  ___  ___| |
        \ // _ \| | | | | |/ _ \/ __|/ _ \ |
        | | (_) | |_| | | | (_) \__ \  __/_|
        \_/\___/ \__,_| |_|\___/|___/\___(_)



"""
win =   """

      __   __                     _       _
      \ \ / /                    (_)     | |
       \ V /___  _   _  __      ___ _ __ | |
        \ // _ \| | | | \ \ /\ / / | '_ \| |
        | | (_) | |_| |  \ V  V /| | | | |_|
        \_/\___/ \__,_|   \_/\_/ |_|_| |_(_)



"""

def print_intro():
    os.system('cls' if os.name == 'nt' else 'clear')
    title = """

        ___  _                       _
       / _ \| |                     (_)
      / /_\ \ | __ _  __ _  ___  ___ _  __ _
      |  _  | |/ _` |/ _` |/ _ \/ __| |/ _` |
      | | | | | (_| | (_| |  __/\__ \ | (_| |
      \_| |_/_|\__, |\__,_|\___||___/_|\__,_|
                __/ |
               |___/

    --- A Text-Based Fantasy Adventure Game ---
    """
    for character in title:
        print(character, end = '', flush = True)
        time.sleep(.01)


def print_s(string, len = .05): # Creates a typing effect and returns after each line.
    for character in string:
        print(character, end = '', flush=True)
        time.sleep(.01)
    time.sleep(len)
    print()

class Paths: # Holds multiple paths for one decision point.
    def __init__(self):
    	self.options = []

    def print_options(self, chosen_option):
        os.system('cls' if os.name == 'nt' else 'clear')
        for line in self.options[chosen_option]:
            print_s(line)



intro = Paths() #Creates the options available at intro (only one option)
# Main game opening text giving the player two choices.
intro_option1 = [
'You wake up disoriented riding in a moving wagon, but you cannot remember where or even who you are',
'Suddenly, a force pushes you off, and you fall onto the unforgiving ground.',
'After awhile, you finally gain enough strength to push yourself up off the cold earth.',
'The sun is starting to set, and you see a dirt road leading towards the Sun(1), ',
'and a different stone path that leads deeper into the forest you came from.(2) ',
''
]
# Adding options to options list
intro.options.append(intro_option1)

path = Paths() #Creates the options available at the path (two options)
# First choice for player
path_option1 = [
'As you are walking down the dirt road you notice huge animal tracks',
'that lead up to the mouth of a cave.',
'Should you continue onward?(1), or follow the tracks?(2)',
''
]
# Second choice for player
path_option2 = [
'Retracing your steps backwards might lead you back to civilizaition, so you wander into the eerie forest.',
'But your skin starts to crawl as the tide of darkness erodes away at the sunlight.',
'You notice a small pond, and you are quite thirsty. Do you stop?(3), or continue onward?(4)',
''
]
# Adding options to options list
path.options.append(path_option1)
path.options.append(path_option2)

sunforest1 = Paths() # A total of 4 outcomes with only 2 options in each playthrough.

# Death by fatigue
sunforest1_option1 = [
'You walk onward down the path finding nothing but the horizon. You walk until you pass out from fatigue.',
'Death visits you in your slumber.',
lose,
''
]
# Cave Path
sunforest1_option2 = [
'You decide to walk into the cave out of sheer curiosity.',
'You see nothing at first, but walk deeper into its depths.',
'It starts to get dark, but then you hear a faint breathing sound.',
'You creep silently closer, and then you see it...',
'It is a giant sleeping dragon!',
'Do you run away?(1) or do you hop on its back? (2)',
''
]
# Lake Path
sunforest1_option3 = [
'You decide to stop at the lake.',
'The water is refreshing as you drink, but then you hear a faint melody acrossed the pond.',
'An mobilzing force draws you towards it.',
'It is a beautiful woman singing an eerie song. She is staring right through you.',
'Her hand reaches out to yours and you take it, not knowing why.',
'She leads you into the water as you peacefully spend death together.',
lose,
''
]
# Continue Onward Path
sunforest1_option4 = [
'You continue forward regretting that you did not stop to drink.',
'The trees and foliage start to look different.',
'Suddenly, you stumble upon a smooth bizarre fruit that looks like a psychadelic potato.',
'Do you eat the fruit?(3), or continue down the path?(4)',
''
]
# Adding options to options list
sunforest1.options.append(sunforest1_option1)
sunforest1.options.append(sunforest1_option2)
sunforest1.options.append(sunforest1_option3)
sunforest1.options.append(sunforest1_option4)

sunforest2 = Paths() # A total of 4 outcomes with only 2 options in each playthrough.
# Death by falling
sunforest2_option1 = [
'You decide to go back out of the cave, but you ',
'cannot remember the path to the entrance.',
'It is so dark in the cave, and you can barely see your feet in front of you.',
'You feel your feet give out from under you and you fall to your death.',
lose,
''
]
# Winning Path
sunforest2_option2 = [
'For some reason, you believe it is a good idea to hop onto the dragon.',
'But then the memories start flooding back and you finally remember who you are.',
'You are a dragon rider, and as you make contact with your dragon Xaria, ',
'the sleeping spell she was under lifts, and you ride off together determined ',
'to find the people that left you to die in the middle of nowhere.',
'Your journey has only just begun.',
win,
''
]
# Death by fruit
sunforest2_option3 = [
'You are ravished, so you bite into the strange looking fruit.',
'It is so sweet and delicious, but immediately you feel something is off.',
'You start to feel light headed and your body feels weak.',
'Your vision starts to get blurry and the ',
'color starts to leak out of your vision.',
'Now the greyscale colors start turning black, and you fall to the ground. Dead.',
lose,
''
]
# Death by fatigue
sunforest2_option4 = [
'You were already so weak, and your body needs some nourishment.',
'You look around and feel like you keep seeing the same trees and foliage',
'over and over again.',
'It feels like you have been walking in circles for hours.',
'You can feel your body shutting down, and you die from exhaustion.',
lose,
''
]
# Adding options to options list
sunforest2.options.append(sunforest2_option1)
sunforest2.options.append(sunforest2_option2)
sunforest2.options.append(sunforest2_option3)
sunforest2.options.append(sunforest2_option4)

def choosePath(opt1, opt2): #Input validation between paths option 1 and option 2.
    logger.debug('choosing path with options: {0} & {1}'.format(opt1,opt2))
    path = ''
    while path != opt1 and path!= opt2: # Input validation
        try:
            path = int(input('Which path will you choose? ({0} or {1}): '.format(opt1, opt2)))
        except:
            print_s('You\'re confused, that\'s not {0} or {1}'.format(opt1,opt2))
    return path


class Game: # Wrapper for game

  def __init__(self):
    logger.debug('Initializing game for first time')
    print_intro()
    self.running = True
    while self.running:
      self.playRound()

  def playRound(self): # Function that runs the game one time
    # Intro
    intro.print_options(0)
    logger.debug('Printing intro')
    choice = choosePath(1,2)

    # Path
    logger.debug('Printing path options')
    path.print_options(choice-1) # Choice is equal to '1' or '2'
    if choice == 1: # Leave towards sun
        choice = choosePath(1,2)
    elif choice == 2: #Back into forest
        choice = choosePath(3,4)
    else:
      	logger.critical('Invalid input into path options')

    # Sun/Forest
    logger.debug('Printing sun or forest options')
    sunforest1.print_options(choice-1) # Choice2 is equal to '1' '2', '3', or '4'
    if choice == 2: # Selected Cave Path
        choice = choosePath(1,2)
    elif choice == 4: # Continue Onward Path
        choice = choosePath(3,4)
    elif choice == 1 or choice == 3: # Died
        logger.debug('Died - asking to play again')
        playAgain = input('Do you want to play again? (Yes or no?): ')
        self.running = (playAgain == 'yes') or (playAgain == 'Yes') or (playAgain == 'y') or (playAgain == 'Y')
        return
    else:
      	logger.critical('Invalid input in sun/forest area')

    # Ending
    logger.debug('Printing ending')
    sunforest2.print_options(choice-1) # Choice3 is equal to '1' '2', '3', or '4'
    playAgain = input('Do you want to play again? (Yes or no?): ')
    self.running = (playAgain == 'yes') or (playAgain == 'Yes') or (playAgain == 'y') or (playAgain == 'Y')

playthrough = Game() #Creates a Game object which runs the game

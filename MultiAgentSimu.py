import numpy as np
import random
## @class Agent
# Agent class
class Agent:

    ## @fn __init__
    # Constructor of Agent class.

    ## @param identity
    # The ID number of an Agent.

    ## @param x
    # The initial position by x.

    ## @param y
    # The initial position by y.
    def __init__(self, identity, x=0, y=0):
        ## @var type
        # The type indicating the class of the Agent.
        self.type = "Plain Agent"

        ## @var id
        # The ID number of an Agent.
        self.id = identity

        ## @var x
        # The position of an Agent by x.
        self.x = x

        ## @var y
        # The position of an Agent by y.
        self.y = y


    ## @fn __repr__
    # The method to display an Agent object in an interactive shell.

    ## @return
    # A string representing the Agent.
    def __repr__(self):
        return self.type + " " + str(self.id) + " at (" + str(x) + "," +str(y) + ")"

    ## @fn __str__
    # The method to display an Agent object as a string.

    ## @return
    # A string representing the Agent.
    def __str__(self):
        return __repr__(self)


## @class Lawnmower
# A Lawnmower agent, inherate from Agent
# @see Agent
class Lawnmower(Agent):
    ## @fn __init__
    # The constructor of Lawnmower, overrides Agent.__init__
    def __init__(self, identity, x, y):
        ## @var x
        # The position of an Agent by x.

        ## @var y
        # The position of an Agent by y.
        super().__init__(identity, x, y)
        ## @var type
        # The type indicating the class of the Agent.
        self.type = "Lawnmower"

    ## @fn forage
    # Forage for resource at point @f$(x^{old},y^{old})@f$ and move to the next point.
    ## @param space
    # The place where the agent is playing in.

    ## @return
    # Nothing
    def forage(self, space):
        space[self.x, self.y] = 0
        self.move(space)
        return


    ## @fn move
    # Move the agent to the next point.
    ## @details
    # Let the height of space be @f$h@f$. \n
    # Let the width of space be @f$w@f$. \n
    # The next position by y is @f$y^{new}=y^{old}+1\mod w@f$. \n
    # The next position by x is @f$x^{new}=\begin{cases}x^{old}+1\mod h,\quad \text{if } y^{old} + 1 = w \\ x^{old}, \quad \text{otherwise} \end{cases}@f$. \n

    ##  @param space
    # The place where the agent is playing in.

    ##  @return
    # nothing
    def move(self, space):
         self.x = (self.x + (self.y + 1)//space.shape[1])%space.shape[0]
         self.y = (self.y + 1)%space.shape[1]

## @class Brownian
# A Brownian agent, inherate from Agent
# @see Agent
class Brownian(Agent):
    ## @fn __init__
    # The constructor of Brownian, overrides Agent.__init__
    def __init__(self, identity, x, y):
        ## @var x
        # The position of an Agent by x.

        ## @var y
        # The position of an Agent by y.
        super().__init__(identity, x, y)
        ## @var type
        # The type indicating the class of the Agent.
        self.type = "Brownian"

    ## @fn forage
    # Forage for resource at point @f$(x^{old},y^{old})@f$ and move to the next point.
    ## @param space
    # The place where the agent is playing in.

    ## @return
    # Nothing
    def forage(self, space):
        space[self.x, self.y] = 0
        self.move(space)
        return


    ## @fn move
    # Randomly move the agent to the next point where there is resource left.

    ##  @param space
    # The place where the agent is playing in.

    ##  @return
    # nothing
    def move(self, space):
         x_new = (self.x + random.randint(-1,1)) % space.shape[0]
         y_new = (self.y + random.randint(-1,1)) % space.shape[1]
         if np.all(space[self.x-1:self.x+2, self.y-1:self.y+2]<=0):
             return
         while space[x_new,y_new] <= 0:
             x_new = (self.x + random.randint(-1,1)) % space.shape[0]
             y_new = (self.y + random.randint(-1,1)) % space.shape[1]
         self.x = x_new
         self.y = y_new
         return


## @fn one_step_simu
# The function to simulate one step in time. Taking care of all the forage and movements of all the agents.

## @param space
# The place where all the agents are playing in.

## @param agent_list
# The list of all the agents objects.

## @return
# Nothing.
def one_step_simu(space, agent_list):
    for i in agent_list:
        i.forage(space)
    return

## @fn print_space
# Print the current status of the space. Indicating the current position of agents, remaining resources.

## @param space
# The place where all agents are playing in.

## @param agent_list
# The list of all agent objects.

def print_space(space, agent_list):
    for i in range(space.shape[0]):
        for j in range(space.shape[1]):
            has_agent = False
            for k in agent_list:
                if i==k.x and j==k.y:
                    has_agent = True
                    print("A"+str(k.id),end=' ')
            if not has_agent:
                if space[i][j] >0:
                    print("X",end='')
                else:
                    print(".",end='')
            print("\t",end='')
            print(" ",end='')
        print()
    return

if __name__=="__main__":
    space = np.ones((5,5))
    agent_list = [Lawnmower(0, 0, 0), Brownian(1,3,3)]
    for i in range(30):
        one_step_simu(space, agent_list)
    print_space(space, agent_list)

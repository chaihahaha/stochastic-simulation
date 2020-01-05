## @mainpage Multi-Agent Simulation
## @note The experiment code for stochastic simulation lab5
## @author Shitong CHAI
## @version 1.0.0
## @date 05/01/2020
## @section Dependency
# Python 3.7.4 (64 bit) on win32. Run this command-line to install dependency: ``` pip install numpy matplotlib scipy ```
## @section Execution
# Run the command-line: ``` python MultiAgentSimu.py ```

import numpy as np
import random
import matplotlib.pyplot as plt
import scipy.stats

## @fn mean_confidence_interval
# The confidence interval with given confidence on sample data.

## @param data
# Sample data as a list

## @param confidence
# The specified confidence probability.

## @return
# The mean value m, and the half length of confidence interval.
def mean_confidence_interval(data, confidence=0.95):
    a = 1.0 * np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    h = se * scipy.stats.t.ppf((1 + confidence) / 2., n-1)
    return m, h

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

        ## @var count
        # Counter to count the number of resource the agent has foraged.
        self.count = 0

    ## @fn __repr__
    # The method to display an Agent object in an interactive shell.

    ## @return
    # A string representing the Agent.
    def __repr__(self):
        return self.type + str(self.id) #+ " current position: (" + str(self.x) + "," +str(self.y) + ")"

    ## @fn __str__
    # The method to display an Agent object as a string.

    ## @return
    # A string representing the Agent.
    def __str__(self):
        return self.__repr__()


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
        if space[self.x, self.y] >0:
            self.count += 1
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
        if space[self.x, self.y] >0:
            self.count += 1
            space[self.x, self.y] = 0
        self.move(space)
        return


    ## @fn move
    # Randomly move the agent to the adjacent point.

    ##  @param space
    # The place where the agent is playing in.

    ##  @return
    # nothing
    def move(self, space):
         #if np.all(space[self.x-1:self.x+2, self.y-1:self.y+2]<=0):
         #    return
         self.x = (self.x + random.randint(-1,1)) % space.shape[0]
         self.y = (self.y + random.randint(-1,1)) % space.shape[1]
         return


## @fn one_step_simu
# The function to simulate one step in time. Taking care of all the forage and movements of all the agents.

## @param space
# The place where all the agents are playing in.

## @param agent_list
# The list of all the agents objects.

## @param t
# The current time of simulation.

## @time_score_matrix
# The matrix storing the resources foraged by each agent over the time span.

## @return
# If there is any remaining resource, return True; otherwise return False.
def one_step_simu(space, agent_list, t, time_score_matrix):
    for i in range(len(agent_list)):
        agent_list[i].forage(space)
        time_score_matrix[i,t]=agent_list[i].count
        remaining = space.shape[0]*space.shape[1] - np.sum(time_score_matrix[:,t])
    return remaining>0

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
                    print(k.type[0]+str(k.id),end=' ')
            if not has_agent:
                if space[i][j] >0:
                    print("X",end='')
                else:
                    print(".",end='')
            print("\t",end='')
            print(" ",end='')
        print()
    return

def exp1_10x10_2agents():
    space = np.ones((10,10))
    agent_list = [Lawnmower(0, 0, 0), Brownian(1,7,7)]
    time = 30
    time_score_matrix = np.zeros((len(agent_list), time))
    for t in range(time):
        has_remain = one_step_simu(space, agent_list, t, time_score_matrix)
        if not has_remain:
            break
    print_space(space, agent_list)


def exp2_100x100_2agents():
    space = np.ones((100,100))
    agent_list = [Lawnmower(0, 0, 0), Brownian(1,30,30)]
    time = 1000000
    time_score_matrix = np.zeros((len(agent_list), time))
    distance = []
    for t in range(time):
        has_remain = one_step_simu(space, agent_list, t, time_score_matrix)
        distance.append(((agent_list[1].x - 30)**2 + (agent_list[1].y - 30)**2)**0.5)
        if not has_remain:
            break

    fig, ax = plt.subplots(1,1)#len(agent_list),1)
    ax.set_title("Resource foraged over time")
    ax.set_xlabel('time')
    ax.set_ylabel('resource foraged')
    for i in range(len(agent_list)):
        ax.plot(np.arange(t+1), time_score_matrix[i,:t+1], label="Resource foraged by "+str(agent_list[i]))
    ax.plot(np.arange(t+1), np.sum(time_score_matrix[:,:t+1], 0), label="Resource foraged by all")
    ax.legend()
    plt.show()

    distance = np.array(distance)
    distance = np.cumsum(distance)
    avg_dis = distance/np.arange(1, len(distance)+1)
    fig, ax = plt.subplots(1,1)
    ax.set_title("Resource foraged by Brownian to the power of 3/4 \nwrt average distance to initial position")
    ax.set_xlabel('average distance')
    ax.set_ylabel('(resource foraged)^(3/4)')
    ax.scatter(avg_dis[:2000], time_score_matrix[1, :2000]**(3/4))
    ax.plot(np.arange(40), np.arange(40)*2, "r--")
    plt.show()

def exp3_conf():
    time = 1000000
    score = []
    for i in range(100):
        space = np.ones((100,100))
        agent_list = [Lawnmower(0, 0, 0), Brownian(1,30,30)]
        time_score_matrix = np.zeros((len(agent_list), time))
        for t in range(time):
            has_remain = one_step_simu(space, agent_list, t, time_score_matrix)
            if not has_remain:
                break
        score.append(time_score_matrix[:, 4000])
    score = np.stack(score, 0)
    m = []
    h = []
    for i in range(100):
        m_a0, h_a0 = mean_confidence_interval(score[:i,0])
        m_a1, h_a1 = mean_confidence_interval(score[:i,1])
        m.append([m_a0, m_a1])
        h.append([h_a0, h_a1])
    m = np.array(m)
    h = np.array(h)
    lower = m-h
    upper = m+h
    fig, ax = plt.subplots(1,1)
    ax.set_title("Confidence interval with confidence 95%")
    ax.set_xlabel("number of experiments")
    ax.set_ylabel("resource foraged when time=4000")
    ax.plot(np.arange(100),m[:,0],"g", label="Mean resource foraged by Lawnmower0")
    ax.plot(np.arange(100),m[:,1],"r", label="Mean resource foraged by Brownian1")
    ax.plot(np.arange(100),lower[:,0], "g--", label="Confidence interval left endpoint")
    ax.plot(np.arange(100),upper[:,0], "g--", label="Confidence interval right endpoint")
    ax.plot(np.arange(100),lower[:,1], "r--", label="Confidence interval left endpoint")
    ax.plot(np.arange(100),upper[:,1], "r--", label="Confidence interval right endpoint")
    ax.legend()
    plt.show()

def exp4_1000x1000_4agents():
    size = 1000
    space = np.ones((size,size))
    agent_list = [Lawnmower(0,random.randint(0,size-1),random.randint(0,size-1)), Brownian(1,random.randint(0,size-1),random.randint(0,size-1)), Brownian(2,random.randint(0,size-1),random.randint(0,size-1)), Brownian(3,random.randint(0,size-1),random.randint(0,size-1))]
    time = 2000000
    time_score_matrix = np.zeros((len(agent_list), time))
    for t in range(time):
        has_remain = one_step_simu(space, agent_list, t, time_score_matrix)
        if not has_remain:
            break

    fig, ax = plt.subplots(1,1)
    ax.set_title("Resource foraged over time")
    ax.set_xlabel('time')
    ax.set_ylabel('resource foraged')
    for i in range(len(agent_list)):
        ax.plot(np.arange(t+1), time_score_matrix[i,:t+1], label="Resource foraged by "+str(agent_list[i]))
    ax.plot(np.arange(t+1), np.sum(time_score_matrix[:,:t+1], 0), label="Resource foraged by all")
    ax.legend()
    plt.show()

def exp5_measure():
    size_of_space = [10, 20, 40, 80, 160, 300, 400, 600, 800, 1000, 1200, 1400,  1600, 1800, 2000, 2200, 2400, 2600, 2800, 3000]
    fraction_lb = []
    for sos in size_of_space:
        space = np.ones((sos,sos))
        agent_list = [Lawnmower(0,random.randint(0,sos-1),random.randint(0,sos-1)), Brownian(1,random.randint(0,sos-1),random.randint(0,sos-1))]
        time = 400*400
        time_score_matrix = np.zeros((len(agent_list), time))
        for t in range(time):
            has_remain = one_step_simu(space, agent_list, t, time_score_matrix)
            if not has_remain:
                break
        fraction_lb.append(agent_list[1].count/(agent_list[0].count + agent_list[1].count))
    avg, h = mean_confidence_interval(fraction_lb[7:])
    print("average percentage:" + str(avg*100)+"%")
    print("confidence interval:[" + str(avg-h) + ", "+str(avg+h)+"]")

    fig, ax = plt.subplots(1,1)
    ax.set_title("Percentage of resource obtained by B1 wrt the size of space")
    ax.set_xlabel("size of space (length of edge)")
    ax.set_ylabel("percentage of resource")
    plt.plot(size_of_space, fraction_lb)
    plt.show()



if __name__=="__main__":
    random.seed(0)
    exp1_10x10_2agents()
    exp2_100x100_2agents()
    exp3_conf()
    exp4_1000x1000_4agents()
    exp5_measure()



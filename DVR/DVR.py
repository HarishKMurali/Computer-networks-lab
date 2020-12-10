import pickle
import socket
import random
import argparse
import threading
import time

ROUTER_PORTS = [48000, 48001, 48002, 48003]
LATENCY = [
  (48000, 48001, 6), (48001, 48000, 6),
  (48000, 48002, 1), (48002, 48000, 1),
  (48000, 48003, 3), (48003, 48000, 3),
  (48001, 48002, 2), (48002, 48001, 2),
  ]

class router:

  ip = '127.0.0.1'

  def __init__(self, port, neighbours):

    self.port = port
    self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    self.socket.bind((self.ip, self.port))

    self.neighbours = neighbours
    # self.routing_table = [(self.port, 0, self.port)]
    self.routing_table = [(x[1], x[2], self.port) for x in LATENCY if x[0] == self.port]

    self.thread = [threading.Thread(target=self.recv_table),threading.Thread(target=self.get_input)]
    time.sleep(2)
    self.view_table(self.routing_table, self.port)
    
    for i in self.thread:
      i.start()
    for i in self.thread:
      i.join()

    self.view_table(self.routing_table, self.port)
    self.socket.close()

  def get_input(self):

    while(True):
      command = input()		# <port number> <data>
      command = command.split(sep=' ')

      port = int(command[0])
      msg = command[1]

      tosend = {
        'type' :'msg',
        'src' :self.port,
        'dst' : port,
        'path' : [self.port],
        'data' :msg
      }
      for i in self.routing_table:
        if i[0] == port:
          self.socket.sendto(pickle.dumps(tosend), (self.ip, i[2]))
          break
        

  def view_table(self, routing_table, port):

    print("Routing table of %d" %(port))
    print(31*"-")
    print("|{:^11}|{:^10}|{:^6}|".format("Router id", "Distance", "Hops"))
    print(31*"-")
    for i in routing_table:
      print("|{:^11}|{:^10}|{:^6}|".format(i[0], i[1], i[2]))
    print(31*"-")
    

  def send_table(self):
    
    print(self.neighbours)
    # time.sleep(3)
    tosend = {
      'type' :'table',
      'Rtable': self.routing_table
    }
    for i in self.neighbours:
      self.socket.sendto(pickle.dumps(tosend), (self.ip, i))
    
    print("Sent")

  def recv_table(self):
    
    self.send_table()
    #print("&")
    while True:
      #print("%")
      time.sleep(1)
      data, (ip, port) = self.socket.recvfrom(1000)
      msg = pickle.loads(data)

      if(msg['type'] == 'table'):
        print(f"\nincoming table from {port}", msg['Rtable'])
        if (self.update_table(msg['Rtable'], port)):	# returns if table is updated
          self.send_table()
          self.view_table()

      elif(msg['type'] == 'msg'):
        if(msg['dst'] == self.port):
          print(f"Message received from {msg['src']}:{msg['data']}")

        else:
          # send 
          msg['path'].append(self.port)
          for i in self.routing_table:
            if i[0] == msg['dst']:
              if i[2] == self.port:
                self.socket.sendto(pickle.dumps(msg), (self.ip,i[0]))
              else:
                self.socket.sendto(pickle.dumps(msg), (self.ip, i[2]))
              break
          
          #self.socket.sendto(pickle.dumps(data), (self.ip, next_hop))
          print(f'[Data] Forward data to next hop {port}')
          path = '->'.join(map(str, msg['path']))
          print(f'[Data] Path: {path}')


  def update_table(self, inc_table, router_id):

    temp = self.routing_table
    router_dist = self.neighbour_distance(router_id)
    for rid in inc_table:
      # check if x.distance + router_distance < existing distancee
      idx = -1
      for i in range(len(self.routing_table)):
        if(self.routing_table[i][0] == rid[0]):
          idx = i; break
      if (idx == -1):
        if (rid[0] != self.port):
          self.routing_table.append((rid[0], rid[1] + router_dist, router_id))
        continue
      if (self.routing_table[idx][1] > rid[1] + router_dist):
        self.routing_table[idx] = (self.routing_table[idx][0], rid[1] + router_dist, router_id)

    self.view_table(self.routing_table, self.port)
    
    if(temp == self.routing_table):
      return 0
    else:
      return 1

  def neighbour_distance(self, router_id):
    return [x[1] for x in self.routing_table if router_id == x[0]][0]

def random_latency(verbose=0):

  for i in range(len(ROUTER_PORTS)):
    for j in range(i+1, len(ROUTER_PORTS)):
      distance = random.randrange(1, 10)
      LATENCY.append((ROUTER_PORTS[i], ROUTER_PORTS[j], distance))
      LATENCY.append((ROUTER_PORTS[j], ROUTER_PORTS[i], distance))

  if(verbose):
    [print(x) for x in LATENCY]
  

if __name__ == "__main__":

  parser = argparse.ArgumentParser()
  parser.add_argument('port', type=int)
  args = parser.parse_args()

  router = router(args.port, [x[1] for x in LATENCY if x[0] == args.port])
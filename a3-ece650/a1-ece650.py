"""
Created on Sat Sep 22 11:24:18 2018
e
@author: Kunal Taneja
"""
import sys
import re
import ast
from decimal import Decimal

class_list = dict()

            
def generate_graph():
    street1 = 1
    street2 = 1
    vertices_for_one_street = list()
    list_vertices_of_intersecting_lines = list()
    graph_edges = list()
    graph_edgeset = set()
    graph_set = set()
    duplicate_edges=list()
    duplicate_edges1=list()
    final_vertices = dict()
    list_intersection = list()
    vertices_intersection = list()
    temp_list = list()

   
    list_values = list(class_list.values())
    total_streets = len(list_values)
    vertices_for_one_street = [None] * total_streets
    
    
    for a in range(0, total_streets):
        temp_list = [i.split(', ', 1)[0] for i in list_values[a]]

        vertices_for_one_street[a] = temp_list
        
        
    for i in range(0, total_streets):
        street1_length = len(vertices_for_one_street[i])
        
        for j in range(i + 1, total_streets):
            street2_length = len(vertices_for_one_street[j])
            while street1 < street1_length:
                while street2 < street2_length:
                    pair1 = vertices_for_one_street[i][street1 - 1]
                    pair2 = vertices_for_one_street[i][street1]
                    pair3 = vertices_for_one_street[j][street2 - 1]
                    pair4 = vertices_for_one_street[j][street2]
                    x1, y1 = ast.literal_eval(pair1)
                    x2, y2 = ast.literal_eval(pair2)
                    x3, y3 = ast.literal_eval(pair3)
                    x4, y4 = ast.literal_eval(pair4)
                    x1 = float(x1)
                    x1=round(x1,2)
                    x2 = float(x2)
                    x2=round(x2,2)
                    x3 = float(x3)
                    x3=round(x3,2)
                    x4 = float(x4)
                    x4=round(x4,2)
                    y1 = float(y1)
                    y1=round(y1,2)
                    y2 = float(y2)
                    y2=round(y2,2)
                    y3 = float(y3)
                    y3=round(y3,2)
                    y4 = float(y4)
                    y4=round(y4,2)
                    A1 = y2 - y1
                    B1 = x1 - x2
                    C1 = A1 * (x1) + B1 * (y1)

                    A2 = y4 - y3
                    B2 = x3 - x4
                    C2 = A2 * (x3) + B2 * (y3)
                    determinant = A1 * B2 - A2 * B1
                    min_x1 = min(x1, x2);min_x2 = min(x3, x4);max_x1 = max(x1, x2);max_x2 = max(x3, x4);
                    min_y1 = min(y1, y2);min_y2 = min(y3, y4);max_y1 = max(y1, y2);max_y2 = max(y3, y4);
                    flag1 = False
                    flag2 = False

                    pair1 = "(" + str(x1) + "," + str(y1) + ")"
                    pair2 = "(" + str(x2) + "," + str(y2) + ")"
                    pair3 = "(" + str(x3) + "," + str(y3) + ")"
                    pair4 = "(" + str(x4) + "," + str(y4) + ")"
                    list_pairs = list((pair1, pair2, pair3, pair4))
                   

                    if (determinant != 0):
                        X = Decimal((B2 * C1 - B1 * C2) / determinant)
                        X = round(X, 2)
                        Y = Decimal((A1 * C2 - A2 * C1) / determinant)
                        Y = round(Y, 2)

                        if (bool(X <= max_x1) & bool(X >= min_x1)):

                            if (bool(Y <= max_y1) & bool(Y >= min_y1)):
                                flag1 = True
                            if (bool(X <= max_x2) & bool(X >= min_x2)):

                                if (bool(Y <= max_y2) & bool(Y >= min_y2)):
                                    flag2 = True
                        if (flag1 == True & flag2 == True):

                            new_vertex = "(" + str(X) + "," + str(Y) + ")"
                            list_vertices_of_intersecting_lines.extend(list_pairs)
                            list_intersection.append(new_vertex)
                            vertices_intersection.append(list_pairs)
                            list_vertices_of_intersecting_lines.append(new_vertex)
                            graph_set = set(list_vertices_of_intersecting_lines)
                            list_vertices_of_intersecting_lines = list(graph_set)
                            for z in range(0, len(list_vertices_of_intersecting_lines)):
                                final_vertices[z] = list_vertices_of_intersecting_lines[z]
                        else:
                            pass
                    elif(pair1==pair4):
                            
                            new_vertex = "(" + str(x4) + "," + str(y4) + ")"
                            list_vertices_of_intersecting_lines.extend(list_pairs)
                            list_intersection.append(new_vertex)
                            vertices_intersection.append(list_pairs)
                            list_vertices_of_intersecting_lines.append(new_vertex)
                            graph_set = set(list_vertices_of_intersecting_lines)
                            list_vertices_of_intersecting_lines = list(graph_set)
                            for z in range(0, len(list_vertices_of_intersecting_lines)):
                                final_vertices[z] = list_vertices_of_intersecting_lines[z]
                    elif(pair2==pair3):
                            new_vertex = "(" + str(x3) + "," + str(y3) + ")"
                            list_vertices_of_intersecting_lines.extend(list_pairs)
                            list_intersection.append(new_vertex)
                            vertices_intersection.append(list_pairs)
                            list_vertices_of_intersecting_lines.append(new_vertex)
                            graph_set = set(list_vertices_of_intersecting_lines)
                            list_vertices_of_intersecting_lines = list(graph_set)
                            for z in range(0, len(list_vertices_of_intersecting_lines)):
                                final_vertices[z] = list_vertices_of_intersecting_lines[z]
                    
                    elif(x1==x2==x3==x4):
                        y_range1=abs(y2-y1)
                        y_range2=abs(y4-y3)
                        if(y_range1 > y_range2):
                            big_line=1
                        elif(y_range2 > y_range1):
                            big_line=2
                        if(big_line == 1):
                            if(y3>min_y1 and y3<max_y1):
                                new_vertex = "(" + str(x3) + "," + str(y3) + ")"
                                list_vertices_of_intersecting_lines.extend(list_pairs)
                                list_intersection.append(new_vertex)
                                vertices_intersection.append(list_pairs)
                                list_vertices_of_intersecting_lines.append(new_vertex)
                                graph_set = set(list_vertices_of_intersecting_lines)
                                list_vertices_of_intersecting_lines = list(graph_set)
                                for z in range(0, len(list_vertices_of_intersecting_lines)):
                                    final_vertices[z] = list_vertices_of_intersecting_lines[z]
                            if(y4>min_y1 and y4<max_y1):
                                new_vertex = "(" + str(x4) + "," + str(y4) + ")"
                                list_vertices_of_intersecting_lines.extend(list_pairs)
                                list_intersection.append(new_vertex)
                                vertices_intersection.append(list_pairs)
                                list_vertices_of_intersecting_lines.append(new_vertex)
                                graph_set = set(list_vertices_of_intersecting_lines)
                                list_vertices_of_intersecting_lines = list(graph_set)
                                for z in range(0, len(list_vertices_of_intersecting_lines)):
                                    final_vertices[z] = list_vertices_of_intersecting_lines[z]
                            
                        if(big_line == 2):
                            if(y1>min_y2 and y1<max_y2):
                                new_vertex = "(" + str(x1) + "," + str(y1) + ")"
                                list_vertices_of_intersecting_lines.extend(list_pairs)
                                list_intersection.append(new_vertex)
                                vertices_intersection.append(list_pairs)
                                list_vertices_of_intersecting_lines.append(new_vertex)
                                graph_set = set(list_vertices_of_intersecting_lines)
                                list_vertices_of_intersecting_lines = list(graph_set)
                                for z in range(0, len(list_vertices_of_intersecting_lines)):
                                    final_vertices[z] = list_vertices_of_intersecting_lines[z]
                            if(y2>min_y2 and y2<max_y2):
                                new_vertex = "(" + str(x2) + "," + str(y2) + ")"
                                list_vertices_of_intersecting_lines.extend(list_pairs)
                                list_intersection.append(new_vertex)
                                vertices_intersection.append(list_pairs)
                                list_vertices_of_intersecting_lines.append(new_vertex)
                                graph_set = set(list_vertices_of_intersecting_lines)
                                list_vertices_of_intersecting_lines = list(graph_set)
                                for z in range(0, len(list_vertices_of_intersecting_lines)):
                                    final_vertices[z] = list_vertices_of_intersecting_lines[z]
                            
                    elif(y1==y2==y3==y4):
                        x_range1=abs(x2-x1)
                        x_range2=abs(x4-x3)
                        if(x_range1 > x_range2):
                            big_line=1
                        elif(x_range2 > x_range1):
                            big_line=2
                        if(big_line == 1):
                            if(x3>min_x1 and x3<max_x1):
                                new_vertex = "(" + str(x3) + "," + str(y3) + ")"
                                list_vertices_of_intersecting_lines.extend(list_pairs)
                                list_intersection.append(new_vertex)
                                vertices_intersection.append(list_pairs)
                                list_vertices_of_intersecting_lines.append(new_vertex)
                                graph_set = set(list_vertices_of_intersecting_lines)
                                list_vertices_of_intersecting_lines = list(graph_set)
                                for z in range(0, len(list_vertices_of_intersecting_lines)):
                                    final_vertices[z] = list_vertices_of_intersecting_lines[z]
                            if(x4>min_x1 and x4<max_x1):
                                new_vertex = "(" + str(x4) + "," + str(y4) + ")"
                                list_vertices_of_intersecting_lines.extend(list_pairs)
                                list_intersection.append(new_vertex)
                                vertices_intersection.append(list_pairs)
                                list_vertices_of_intersecting_lines.append(new_vertex)
                                graph_set = set(list_vertices_of_intersecting_lines)
                                list_vertices_of_intersecting_lines = list(graph_set)
                                for z in range(0, len(list_vertices_of_intersecting_lines)):
                                    final_vertices[z] = list_vertices_of_intersecting_lines[z]
                            
                        if(big_line == 2):
                            if(x1>min_x2 and x1<max_x2):
                                new_vertex = "(" + str(x1) + "," + str(y1) + ")"
                                list_vertices_of_intersecting_lines.extend(list_pairs)
                                list_intersection.append(new_vertex)
                                vertices_intersection.append(list_pairs)
                                list_vertices_of_intersecting_lines.append(new_vertex)
                                graph_set = set(list_vertices_of_intersecting_lines)
                                list_vertices_of_intersecting_lines = list(graph_set)
                                for z in range(0, len(list_vertices_of_intersecting_lines)):
                                    final_vertices[z] = list_vertices_of_intersecting_lines[z]
                            if(x2>min_x2 and x2<max_x2):
                                new_vertex = "(" + str(x2) + "," + str(y2) + ")"
                                list_vertices_of_intersecting_lines.extend(list_pairs)
                                list_intersection.append(new_vertex)
                                vertices_intersection.append(list_pairs)
                                list_vertices_of_intersecting_lines.append(new_vertex)
                                graph_set = set(list_vertices_of_intersecting_lines)
                                list_vertices_of_intersecting_lines = list(graph_set)
                                for z in range(0, len(list_vertices_of_intersecting_lines)):
                                    final_vertices[z] = list_vertices_of_intersecting_lines[z]
                    
                            
                                
                        
                                
                        



                        

                    street2 = street2 + 1
                street1 = street1 + 1
                street2 = 1
            street1 = 1

    sys.stdout.write( "V ")
    sys.stdout.flush()
    sys.stdout.write(str(len(final_vertices))+'\n')
    sys.stdout.flush()

    for b in range(0, len(list_intersection)):
        #print "i"
        #print (len(list_intersection))
        intersection_pt = list_intersection[b]
        vertexlist = vertices_intersection[b]
        [pair1, pair2, pair3, pair4] = vertexlist
        edge_intersection = final_vertices.keys()[final_vertices.values().index(intersection_pt)]
        participating_vertex1 = final_vertices.keys()[final_vertices.values().index(pair1)]
        participating_vertex2 = final_vertices.keys()[final_vertices.values().index(pair2)]
        participating_vertex3 = final_vertices.keys()[final_vertices.values().index(pair3)]
        participating_vertex4 = final_vertices.keys()[final_vertices.values().index(pair4)]
        

        edge1 = "<" + str(edge_intersection) + "," + str(participating_vertex1) + ">"

        edge2 = "<" + str(edge_intersection) + "," + str(participating_vertex2) + ">"
        edge3 = "<" + str(edge_intersection) + "," + str(participating_vertex3) + ">"
        edge4 = "<" + str(edge_intersection) + "," + str(participating_vertex4) + ">"

        edgelist = list((edge1, edge2, edge3, edge4))
        graph_edges.extend(edgelist)
        graph_edgeset = set(graph_edges)
        graph_edges = list(graph_edgeset)
        distinct_new_vertices = list()
    
    for g in range(0,len(graph_edges)):
        edge_1 = graph_edges[g]
        edge_1 = re.sub('<', '(', edge_1)
        edge_1 = re.sub('>', ')', edge_1)
        pair1,pair2 = ast.literal_eval(edge_1)
        if(pair1==pair2):
            delete="<" + str(pair1) + "," + str(pair2) + ">"
            duplicate_edges.append(delete)

        for h in final_vertices:
            v1=final_vertices[pair1]

            v2=final_vertices[pair2]

            v_x1,v_y1=ast.literal_eval(v1)
            v_x2,v_y2=ast.literal_eval(v2)
            min_x1 = min(v_x1, v_x2)
            max_x1 = max(v_x1, v_x2)
            min_y1 = min(v_y1, v_y2)
            max_y1 = max(v_y1, v_y2)
            check_v1_v2=final_vertices[h]

            c_x,c_y=ast.literal_eval(check_v1_v2)
            if((bool(c_x!=min_x1) & bool( c_x !=max_x1)) | ((bool(c_y!=min_y1) & bool(c_y!=max_y1)))):
                if(bool(c_x <= max_x1) & bool(c_x >= min_x1)):
                    if(bool(c_y <= max_y1) & bool(c_y >= min_y1)):
                        del_duplicate="<" + str(pair1) + "," + str(pair2) + ">"

                        duplicate_edges.append(del_duplicate)
                        duplicate_edges_set=set(duplicate_edges)
                        duplicate_edges=list(duplicate_edges_set)
                        

    for k in range(0,len(duplicate_edges)):
        graph_edges.remove(duplicate_edges[k])
    
    for l in range(0,len(graph_edges)):
        for l1 in range(l+1,len(graph_edges)):
            edge_1 = graph_edges[l]
            edge_1 = re.sub('<', '(', edge_1)
            edge_1 = re.sub('>', ')', edge_1)
            pair1,pair2 = ast.literal_eval(edge_1)
            edge_2 = graph_edges[l1]
            edge_2 = re.sub('<', '(', edge_2)
            edge_2 = re.sub('>', ')', edge_2)
            pair3,pair4 = ast.literal_eval(edge_2)
            if(pair1==pair4 and pair2==pair3):
                delete="<" + str(pair1) + "," + str(pair2) + ">"
                duplicate_edges1.append(delete)
                duplicate_edges_set1=set(duplicate_edges1)
                duplicate_edges1=list(duplicate_edges_set1)
    
    for m in range(0,len(duplicate_edges1)):
        graph_edges.remove(duplicate_edges1[m])
    for d in range(0, len(graph_edges)):
        pair = graph_edges[d]
        pair = re.sub('<', '(', pair)
        pair = re.sub('>', ')', pair)
        x_coord, y_coord = ast.literal_eval(pair)
        distinct_new_vertices.append(x_coord)
        distinct_set = set(distinct_new_vertices)
        distinct_new_vertices = list(distinct_set)
        #print distinct_new_vertices
        for e in range(0, len(distinct_new_vertices)):
            for f in range(e+1,len(distinct_new_vertices)):
                edge_between = "<" + str(distinct_new_vertices[e]) + "," + str(distinct_new_vertices[f]) + ">"
                graph_edges.append(edge_between)
                    
                graph_set = set(graph_edges)
                graph_edges = list(graph_set)
                

    sys.stdout.write("E {")
    sys.stdout.flush()
    count=len(graph_edges)
    for u in graph_edges:
        sys.stdout.flush()
        sys.stdout.write(u)
        sys.stdout.flush()
        count=count-1
        if(count):
            sys.stdout.write(',')
            sys.stdout.flush()
    sys.stdout.write("}" + '\n')
    sys.stdout.flush()
        
    
def change_validity(street):
    if street in class_list:
        return True
    else:
            return False
def add_possible(street):
    if street in class_list:
        return False
    else:
            return True


    
def street_validity(street):
    if all(x.isalpha() or x.isspace() for x in street):
        return True
    else:
        return False


def balanced_paranthesis(location):
    a = []
    balanced = True
    index = 0
    while index < len(location) and balanced:
        check = location[index]
        if check == "(":
            a.append(check)
        elif check == ")":
            if len(a) == 0:
                balanced = False
            else:
                a.pop()

        index += 1

    return balanced and len(a) == 0

def location_validity(location):
    regular_exp = r'\(-?\d+,-?\d+\)'
    #regular_exp2= r'\(-?\d+\.?\d*,-?\d+\.?\d*\)'
    compiled_regex = re.compile(regular_exp)
    #compiled_regex2= re.compile(regular_exp2)
    if(compiled_regex.match(location)):
        return True
   # if(compiled_regex2.match(location)):
   #     return True
    else: 
        return False

def user_input():
    command=sys.stdin.readline()
    return command.replace('\n','')

    
def main():
    while True:
        try:
            command=raw_input()
            if(command[0]=='r'):
                y=re.split(' +"|"|',command)
            else:
                y=re.split('" +| +"',command)
            if(len(y)==1):
                choice=y[0]
            elif(len(y)==2):
                choice=y[0]
                street=y[1]
                street=street.lower()   
            elif(len(y)==3):
                choice=y[0]
                street=y[1]
                street=street.lower()
                location=y[2]
            else:
                sys.stderr.write("Error: " + "Wrong command, please enter command in format: " +" a \"street_name\" gps coordinates" + '\n')
                sys.stdout.flush()
                continue
            
            
            
            
            if choice == 'a':
                try:
                    if(street_validity(street)):
                        if(balanced_paranthesis(location)):
                            if(add_possible(street)):
                                location=re.sub(' +','',location)
                                location=re.sub('\)\(',') ( ',location)
                                location=re.sub('\( ','(',location)
                                location=location.split(' ')
                                if all(location_validity(i) for i in location):
                                    class_list[street] = location
                                else:
                                    sys.stderr.write("Error: " + "Please enter vertices of street in valid format (try only integer input)!!" + '\n')
                                    sys.stdout.flush()
                            else:
                                sys.stderr.write("Error: " + "Street already added " + '\n')
                                sys.stdout.flush()
                        else:
                            sys.stderr.write("Error: " + "Paranthesis of vertices do not match, Try again!!" +'\n')
                            sys.stdout.flush()
                    else:
                        sys.stderr.write("Error: " + "Invalid Street Name or try giving atleast one whitespace between street name and gps coordinates!!" + '\n')
                        sys.stdout.flush()
                except UnboundLocalError:
                    sys.stderr.write("Error: " + "Please Enter the whole command as: " + "a 'street name' gps-coordinates" + '\n')
                    sys.stdout.flush()
                    
                    
                    
                    
               
            elif choice == 'c':
                try:
                    if(change_validity(street)):
                        if(street_validity(street)):
                            if(balanced_paranthesis(location)):
                                location=re.sub(' +','',location)
                                location=re.sub('\)\(',') ( ',location)
                                location=re.sub('\( ','(',location)
                                location=location.split(' ')
                                if all(location_validity(i) for i in location):
                                    class_list[street] = location
                                else:
                                    sys.stderr.write("Error: " + "Please enter vertices of street in valid format!!" + '\n')
                                    sys.stdout.flush()
                            else:
                                sys.stderr.write("Error: " + "Paranthesis of vertices do not match, Try again!!" + '\n')
                                sys.stdout.flush()
                        else:
                            sys.stderr.write("Error: " + "Invalid Street Name or try giving atleast one whitespace between street name and gps coordinates!!" + '\n')
                            sys.stdout.flush()
                    else:
                        sys.stderr.write("Error: " + "Street cannot be altered because street is not added yet  or has been removed or enter some coordinates to change!! " + '\n')
                        sys.stdout.flush()
                except UnboundLocalError:
                    sys.stderr.write("Error: " + "Please Enter the whole command as: " + "c 'street name' gps-coordinates" + '\n')
                    sys.stdout.flush()
            
            
            elif choice == 'r':
                try:
                    try:
                            del class_list[street]
                    except KeyError:
                        sys.stderr.write("Error: " + street + " not available to delete or has been removed already!!" + '\n')
                        sys.stdout.flush()
                except UnboundLocalError:
                    sys.stderr.write("Error: " + "Please Enter the whole command as: " + "r 'street name'" + '\n')
                    sys.stdout.flush()
    
            elif choice == 'g':
                generate_graph()
                sys.stdout.flush()
              
            else:
                sys.stderr.write("Error: " + "Wrong command, please select in a , c , r or g only!!" + '\n')
                sys.stdout.flush()
        except:
            break
        sys.stdout.flush()
if __name__ == '__main__':
    main()

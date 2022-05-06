# Triangle Quad Tree Problem!

  <h2> Introduction </h2>

  Part 1: Given a set of 2D points, build a triangle quad tree & also traverse it! </br>
  Part 2: Given a TIN, build a Terrian tree, Grid & VT relation! </br>

  <h2> Required Material for Part 1 & Part 2</h2>

    0. python3 </br>
    1. A txt file with the points(Example shown below)
    2. You should have matplotlib, scipy, numpy installed
    3. Your txt file for part 1 should be inside the './partOne/dataPartOne/' folder!
    4. Your txt file for part 2 should be inside the './partTwo/dataPartTwo/' folder!

  <h2>Run instructions </h2>

    0. Downlaod this zip file </br> 
    1. Open Terminal </br>
    2. Type: cd triangleQuadTree/ </br>
    
    3. To run Part 1:
    3. Type: python3 partOne/main_test_demo.py [point_file_path] [capacity]   </br>
    3. Example: python3 partOne/main_test_demo.py ./partOne/dataPartOne/input_vertices_1.pts 1   </br>


    4. To run Part 2
    4. Type: python3 partTwo/main_test_demo.py [point_file_path] [capacity]   </br>
    4. Example: python3 partTwo/main_test_demo.py ./partTwo/dataPartOne/input_vertices_1.pts 1        </br>
    4. Example: python3 partTwo/main_test_demo.py ./partTwo/dataPartTwo/test_bathymetric.pts 15        </br>

    4. Follow instrutions for running task 1, 2 and 3

    5. For Running part 2, the settings will be taken in this order:
    Enter Starting Point of Grid - X Coordinate: 
    Enter Starting Point of Grid - Y Coordinate: 
    Enter Cell Height: 
    Enter Cell Width: 
    Enter number of rows: 
    Enter number of cols: 

    6. Check below to see the settings parameters for the grid!
    6. input_vertices_1.pts (50, 50, 20, 20, 20, 20)  #Order will be the same as above instructions (point 5)
    6. input_vertices_2.pts (50, 50, 20, 20, 20, 20)  #Order will be the same as above instructions (point 5)
    6. input_vertices_3.pts (230, 130, 0.2, 0.2, 40, 40)  #Order will be the same as above instructions (point 5)
    6. test_bathymetric.pts (-77500, 546000, 200, 200, 50,50)  #Order will be the same as above instructions (point 5)
    6. test_chm.pts (230, 130, 2, 2, 20, 20)  #Order will be the same as above instructions (point 5)

    5. Enjoy!

  <h2>Notes": </h2>
  
    0. This program was built using Python3</br>
    1. Please use your mouse to move, pan around the TIN and the 2D grid!
    2. Press 'q' on your keyboard to kill the matplotlib window
    3. Use capacties 1 for input_vertices_x files and 15 for all other files





============================================================================================
Computational Geometry: Spatial Data Structures,  Voronoi Diagram and Delaunay Triangulation
============================================================================================


:author: David Coeurjolly


.. |imp| replace:: `\Rightarrow`:math:



Point Set Spatial Data Structures
=================================


Range Queries
-------------

**Problem setting**

* Define a structure on point set to efficiently answer to range queries: given a range, output the set of points belonging to it



**Dimension 1**

* Set of points in a line `S=\{x_i\}`:math:
* Interval queries `[l,r]`:math:, returns  `\{x_j\}\subset S`:math: with  `x_j\in[l,r]`:math:
* Data structure: *balanced binary search tree*

|imp| O(n) storage and `O(nlogn)`:math: construction time, then `O(k + log(n))`:math: per query (k is number of reported points)





Regular but recursive spatial decomposition: QuadTree/OctTree
-------------------------------------------------------------


**Idea**

* Regular `2^d`:math:-ary tree
* Recursive construction and data placed to leaves
* Usually, one datum per leaf
* |imp| *depth depending in the min distance between two points*
* |imp| *could be unbalanced*
* |imp| *fast bottom-up/top-down construction algorithms*

.. list-table::

 * -  .. image:: _static/images/CG/quadtree.*
          :width: 60%
          :align: center

   -  .. image:: _static/images/CG/octree.*
          :width: 100%


Implementation: Pointerless Trees
---------------------------------

**Idea**

* Pointer based implementation is quite expensive (4 or 8 pointer per tree node)
* |imp| Binary encoding (*Morton codes*) and implicit hierarchical structure



.. list-table::

 * -  .. image:: _static/images/CG/quadtree1.*
          :width: 60%
          :align: center

   -  .. image:: _static/images/CG/quadtree2.*
          :width: 100%



.. image:: _static/images/CG/morton.*
      :width: 50%
      :align: center


Implementation: Pointerless Trees (again)
-----------------------------------------

**Ctd.**

* At construction, when we increase the depths, we just add 2 bits (2D) or 3 bits (3D) suffixes 
* One datum =  one binary code
* Localizing a point = *bit code interleaving*  on binary representation of point coordinates


* Final encoding: hash map on binary morton codes
   .. math:: 
        \begin{align*}
          x &= x_1x_2\ldots x_m\\
          y &= y_1y_2\ldots x_m\\
          morton_l(x,y) &= \bar{0}1 y_1x_1y_2x_2\ldots y_lx_l
        \end{align*}



   .. image:: _static/images/CG/hashquadtree.*
       :width: 60%
       :align: center


QuadTree/Octree conclusion
--------------------------

* Nice pointerless encoding
* Many operations on quadtree/octree (sibling nodes, ....)
* Data can be stored in intermediate nodes


... but

* Bad point distributions lead to unbalanced structures
* Worst case quadratic time construction (naive top-down)


Kd-Tree structure
-----------------

**Description**

* Hierarchical structure
* Recursive construction and we use axis parallel constraints to  subdivide the space



Pseudo-code in 2D:

.. code-block:: c

  BuildKdTree(S, depth)
    if |P|=1
       return a leaf containing this point

    if depth is even
       Let l be the vertical line with median x-coordinate
       Split S w.r.t. l -> S1 and S2
       
    if depth is odd
       Let l be the horizontal line with median y-coordinate
       Split S w.r.t. l -> S1 and S2
       
    SubTree1 = BuildKdTree(S1,depth + 1)
    SubTree2 = BuildKdTree(S2,depth + 1)

    return Tree( l , SubTree1, SubTree2)
 



Computational cost
------------------


* *Median computation of a vector of scalars* `O(n)`:math: 

* *Recursive cost* `T(n) = O(n) + 2T(n/2)`:math: 


|imp| **KdTree construction in** `O(n log n)`:math:, O(n) storage





**Example**   <Cf board>

FYI: Median of a scalar vector
------------------------------

**Random algorithm**

.. code-block:: c

  QuickSelect(A, k) 
    Pick a pivot element p randomly from A
    Split A into LESS and GREATER sets
    L =  number of elements in the LESS array
    if (L == k-1) 
       return p;

    if (L > k-1)  
       return QuickSelect(LESS, k)

    if (L < k-1) 
       return QuickSelect(GREATER, k - L - 1)

|imp| *randomized O(n) expected time to get the k-rank element*


FYI: Median of a scalar vector
------------------------------

**Deterministic algorithm**

.. code-block:: c

  QuickSelect(A, k) 
    Group the array into n/5 groups of size 5
    Find the median of each group  //Let M be the set of medians

    p = QuickSelect(M,k)  // median of the medians
 
    Split A into LESS and GREATER sets
    L =  number of elements in the LESS array
    if (L == k-1) 
       return p;

    if (L > k-1)  
       return QuickSelect(LESS, k)

    if (L < k-1) 
       return QuickSelect(GREATER, k - L - 1)

|imp| *Deterministic O(n) time to get the k-rank element* (details skipped but I encourage you to have a look!)



KdTree: Advantages/Drawbacks
----------------------------


* Balanced structure (no dependency on the point distribution)

* Binary tree: during a decent, we just have to compare one coordinate to select the subtree


... but...

* Rectangular range query in `O(\sqrt{n} + k)`:math:



Range query in kd-Tree
----------------------

**Algo**

.. code-block:: c

  RangeQueryKdTree(node, Range)

    //Stop
    if node is a leaf
       return the p point in node if p in Range
       
    //left child
    if region(leftChild(node)) is fully contained in Range
       return all points in the subtree leftChild(node) //(A)
    else
       if region(leftChild(node) intersects Range
         return RangeQueryKdTree( leftChild(node) , Range)

    //right child
    if region(rightChild(node)) is fully contained in Range
       return all points in the subtree rightChild(node) //(B)
    else
       if region(rightChild(node) intersects Range
         return RangeQueryKdTree( rightChild(node) , Range)


**Hints**

* Cases (A) and (B) are in O(k)
* We need to bound the number of visited nodes which are not in the output (= number of nodes with line intersection Range)



Proof Ctd.
----------

* We focus on the number of regions intersected by any vertical line `l`:math: (left/right interval in Range)
* Let Q(n) be the number of such regions in a kdTree with n vertex whose root is a vertical line

**Obs1** If `l`:math: is vertical and the constraint of the root is vertical, `l`:math: only crosses one of the root children regions

**Obs2** If `l`:math: is vertical and the constraint of the root is horizontal, `l`:math: crosses both root children regions

|imp| *two step recurrence (subtress of depth 2 have n/4 points)*

   .. math::
       Q(n) = 2 + 2Q(n/4) 
   

|imp| `Q(n) = O(\sqrt{n})\quad \Box`:math:
 


**Range tree structure in dimension d** with `O(nlog^{d-1}n)`:math: storage  constructed in `O(n\log^{d-1}n)`:math: can answer to hyperrectangular range queries in `O(\log^dn + k)`:math:)      


Voronoi Diagram / Delaunay Triangulation
========================================


(Some images from Olivier Devillers, INRIA Sophia-Antipolis)


Simple Construction
-------------------

**Setting** Given a set of sites `\{S_i\}`:math:, answer to closest site queries



.. container:: build animation


 .. image:: _static/images/CG/delaunay-init.*
        :width: 100%  

 .. image:: _static/images/CG/delaunay-1.*
        :width: 100%  

 .. image:: _static/images/CG/delaunay-2.*
        :width: 100%  


 .. image:: _static/images/CG/voronoi1.*
        :width: 100%  

 .. image:: _static/images/CG/voronoi-delaunay.*
        :width: 110%  


Closest site query
------------------


**Find closest site <=> point location in a Voronoi diagram**


**Key Property for Delaunay triangle/edges** Empty circle property



 .. image:: _static/images/CG/delaunay-empty.*
        :width: 80%  


Remember the  `InCircle(p,q,r,s)`:math: predicate ?
 

InCircle predicate
------------------
 
 .. image:: _static/images/CG/orientation_circle.*
         :width: 40%
         :align: center


* true if `s`:math: lies inside the circumscribing circle of the triangle (p,q,r)


   .. math::
     InCircle(p,q,r,s) = sign \left | \begin{array}{cccc} 1 & p_x & p_y & p_x^2+py^2\\1 & q_x & q_y & q_x^2+q_y^2\\1 & r_x & r_y & r_x^2+r_y^2\\1 & s_x & s_y & s_x^2+s_y^2\end{array}\right|


Properties of the Delaunay Triangulation
----------------------------------------

**Triangulation where smallest angle is maximal**

  .. image:: _static/images/CG/smallest.*
      :width: 30%

*true for all angles in lexicographic order*



    .. image:: _static/images/CG/smallest1.*
        :width: 60%  

    .. image:: _static/images/CG/smallest2.*
         :width: 60%  


Properties Ctd.
---------------

**Many deeper properties** 

* Regularity of the triangulation
* Kind of optimal spectral properties
* ...


Widely used for surface reconstruction and finite element computations for example


    .. image:: _static/images/CG/meshing.*
         :width: 50%
           

Delaunay Construction
---------------------

**Local Delaunay tests**

Given a triangle T(a,b,c) and adjacent triangles T(a,b,p), T2(a,c,q) and T3(b,c,r), T is locally delaunay if `InCircle`:math:  predicates (a,b,c,p) (a,b,c,q) and (a,b,c,r) fails

**Main result**

   Everywhere locally Delaunay `\Leftrightarrow`:math: Globally Delaunay





**Naive Algorithm**

* Start from any valid triangulation
* While there is an invalid triangle w.r.t. empty circle property,  perform *edge flipping*
* |imp| **the algorithm stops and produces a correct Delaunay triangulation**

   .. image:: _static/images/CG/edgeflipping.*
       :width: 60%



Incremental Delaunay Construction
---------------------------------


**Idea**

* Add points one by one
* While inserting a point, we construct a valid triangulation 
* At each step, we update the triangulation to keep the Delaunay property


**SubProblems**


* *Localization* of a point in a given Delaunay Triangulation

     returns the triangle T containing p

* *Local Triangulation* of a polygon

    locally triangulate the *one-ring* of T  + p

* *Update of invalid triangles* 



    maintain Delaunay property
 

Detecting Conflicts
-------------------



.. container:: build animation


 .. image:: _static/images/CG/delinc1.*
        :width: 80%  
        
 .. image:: _static/images/CG/delinc2.*
        :width: 80%  

 .. image:: _static/images/CG/delinc3.*
        :width: 80%  

 .. image:: _static/images/CG/delinc4.*
        :width: 80%   
                


Overall Incremental Construction
--------------------------------


.. container:: build animation


 .. image:: _static/images/CG/delinc1.*
        :width: 80%  
      
 .. image:: _static/images/CG/delinc-hole.*
        :width: 80%  
        
 .. image:: _static/images/CG/delinc-add.*
        :width: 80%  


Computational Cost
------------------

**Straightforward analysis**

* Localization = O(n)
* Local triangulation + update = O(n)

|imp| `O(n^2)`:math:



  .. image:: _static/images/CG/delworstcase.*
        :width: 50%
        :align: center


        
Optimizing the Localization
---------------------------
        
**Main Idea** 

* Localize the point using sequence of displacement in the triangulation

* We are looking for  better *expected* computational cost 


   .. image:: _static/images/CG/delwalk.* 
        :width: 60%


Straight-line walk
------------------

**Idea**

* We move from a triangle to the next one if the shared edge is crossed by the straight line
* only "Orientation" predicates are used
* Two orientation tests per triangle

* `O(\sqrt{n})`:math: for uniform point distributions

.. list-table::
 

   * - .. image:: _static/images/CG/delwalk1.*
            :width: 100%

     - .. image:: _static/images/CG/delwalk2.*
            :width: 100%

     - .. image:: _static/images/CG/delwalk3.*
            :width: 100%

     - .. image:: _static/images/CG/delwalkend.*
            :width: 100%


**Important** bad orientation predicates may lead to cycles in the walk...

Optimized walks
---------------

**Visibility walk**

* Localize the point w.r.t. linear constraint
* One orientation per triangle


.. list-table::
 

   * - .. image:: _static/images/CG/delvis1.*
            :width: 80%
            :align: center

     - .. image:: _static/images/CG/delvis2.*
            :width: 80%
            :align: center

  
**Jump & Walk**

**Hierarchical structure**


**...**


**Delaunay Triangulation can be obtained in** `O(nlogn)`:math: (O(n) storage) 



Alternative algorithms: Sweep lines
-----------------------------------

**Idea**

* Move a line with increasing abscissa
* Construct partial Delaunay triangulation on special events during the sweeping





.. list-table::
 

   * - .. image:: _static/images/CG/sweep1.*
            :width: 80%
            :align: center

     - .. image:: _static/images/CG/sweep2.*
            :width: 80%
            :align: center

   * - .. image:: _static/images/CG/sweep3.*
            :width: 80%
            :align: center

     - .. image:: _static/images/CG/sweep4.*
            :width: 80%
            :align: center






Alternative algorithms: Divide and Conquer
------------------------------------------

**Idea**

* Recursive construction
* Split the point set according to median (along the x-axis for instance) O(n)
* Union of two Delaunay triangulations  O(n)
* |imp| `O(n\log n)`:math:



.. list-table::
 

   * - .. image:: _static/images/CG/deldivide.*
            :width: 60%
            :align: center

     - .. image:: _static/images/CG/deldivide2.*
            :width: 60%
            :align: center

   * - .. image:: _static/images/CG/deldivide3.*
            :width: 60%
            :align: center

     - .. image:: _static/images/CG/deldivideend.*
            :width: 60%
            :align: center


Alternative algorithms: as Convex Hull in 3-space
-------------------------------------------------

**Idea**

* Delaunay triangulation  has the same structure as the convex hull of projected points to a paraboloid
* `O(n\log{n})`:math: for 3D convex hull |imp| `O(n\log{n})`:math: for 2D Delaunay triangulation


   .. image:: _static/images/CG/del3space.*
         :width: 70%      

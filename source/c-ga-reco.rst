=========================================================================
Computational Geometry: Digital Delaunay Triangulation and Reconstruction
=========================================================================

:author: David Coeurjolly



Digital Delaunay Triangulation
==============================

Description
-----------

**Input**

* Points from the digital contour of an object

     *local consistency of points*

* Points in `[0,N]^d`:math:

     *specific integer based structures*

**Let's start with good news**

* Exact InCircle predicates thanks to integer coordinates


**... and the bad ones**

* On the regular lattice, we have many co-cyclic points
* No `\epsilon`:math: perturbation can be done


**Questions**

  *Can we expect better bounds for Delaunay structure?*


Digtial Contour
---------------

**Delaunay triangulation from minimum spanning tree**

.. admonition:: Thm. [Devillers]

   If the **Euclidean Minimum Spanning Tree** of the input point set,
   the whole triangulation can be constructed in expected time `O(n
   log^* n)`:math:


(`log^* n=inf\{k;log(k)n≤1\}`:math: hence for `16<n≤65532`:math:, `log^*
n=4`:math:,  `log^* n= 5`:math:  for `n<2^{65532}`:math:)

.. image:: _static/images/CG/DelDiscret/Minimum_spanning_tree.*
      :width: 30%
      :align: center

**Why?**

* All edges of the EMST are Delaunay Edges
* *Even true for any spanning subgraph of the Delaunay structure with
  maximal degree d*

Digtial Contour (bis)
---------------------

**Main observation**

.. admonition:: Thm.

      The polyline defined from digital contour points is a Delaunay
      spanning graph with maximal degree 2


.. admonition:: Thm.

    **Expected time for Delaunay construction for digital contour is in** `O(n log^* n)`:math:


* Deterministic algorithm exists in dimenion 2

.. list-table::


   * - .. image:: _static/images/CG/DelDiscret/delaunay-5.png
            :width: 100%
            :align: center

     - .. image:: _static/images/CG/DelDiscret/delaunay-10.png
            :width: 100%
            :align: center

     - .. image:: _static/images/CG/DelDiscret/delaunay-100.png
            :width: 100%
            :align: center



Digital Straight Segment Pattern
--------------------------------

**Observation**

For digital straight segment patterns, can we recover the Delaunay
structure from arthimetic properties ?






Digital Points
--------------

**Setting**

* Convxe



Delaunay Based Differential Estimators
======================================


Alliez,Merigot, ...


Voronoi Based Reconstruction
============================

cone / cocone

=====================================
Digital Geometry: Volumetric Analysis
=====================================
:author: David Coeurjolly



Distance Transformation/Voronoi Map
===================================

Problem setting
---------------

**Distance transformation**

.. admonition:: Def.

  At each point `p`:math: of a shape `X`:math:, we want the smallest distance to `q\in\bar{X}`:math:



.. list-table::

  - * .. image:: _static/images/DT/homme.*
           :width: 100%

    * .. image:: _static/images/DT/homme_edt_eq.*
           :width: 100%

    * .. image:: _static/images/DT/homme_circ.*
           :width: 100%



`\Rightarrow`:math: **We need**

* A metric definition on `\mathbb{Z}^n`:math:
* Algorithms to compute the DT


Why the DT ?
------------

**Very usefull**

* To extract metric information from digital objects
* Implicit representation of surfaces
* Differential estimators form DT and Voronoi Diagram
* Representation as a union of balls


**...for many applications**

* Shape description
* Motion planning
* Image synthesis
* Material Sciences
* ...


.. list-table::

  - * .. image:: _static/images/DT/spheretree-single.*
          :width: 60%

    * .. image:: _static/images/DT/contour.*
          :width: 60%

    * .. image:: _static/images/DT/contour_circ.*
          :width: 60%

Example: curvature from DT
--------------------------

**Idea**

Shape `\rightarrow`:math: Boundary `\rightarrow`:math: Distance field `\rightarrow`:math: Implicit representation `f: (x,y)\rightarrow \mathbb{R}`:math:

 .. math::
           f(x,y)&=0\\
           \vec{g}(x,y)&=(I_x,I_y)^T\\
           \vec{t}(x,y)&=\frac{(-I_x,I_y)^T}{\sqrt{I_x^2+I_y^2}}\\
           k&=\frac{-t^THt}{\|\vec{g}\|}, \quad H=
           \left [ \begin{array}{cc}
             I_{xx} & I_{xy}\\
             I_{yx} & I_{yy}
           \end{array}\right ]



Application example 1: Snow Micro-structure Analysis
----------------------------------------------------


**Objectives**

* X-tomographic 3D images of snow samples
* We need to extract geometrical information such as

  * Density, specific surface
  * Curvature map to guide metamorphosis
  * *Thickness, percolation path, ...* (`\Rightarrow`:math: DT)


.. list-table::

  - * .. image:: _static/images/DT/echantillonSurface.*
       :width: 100%

    * .. image:: _static/images/DT/M2DISCO8.*
       :width: 90%

    * .. image:: _static/images/DT/Courb08iso_600_300_256p2_000.*
       :width: 90%





Application example 2: Metallic Foam Description
------------------------------------------------


**Objectives**

* X-ray tomographic 3D images of metallic/polymer foam  (used for catalytic processes)
* We need to extract geometrical information such as

  * Structural Complexity  of the 1D structure
  * *Thickness, percolation path, thermodynamic diffusion paths, ...* (`\Rightarrow`:math: DT)


.. list-table::

  - * .. image:: _static/images/DT/mousse_surface.*
       :width: 100%

    * .. image:: _static/images/DT/mousse_DT.*
       :width: 100%


Metric in Digital Space
-----------------------


.. admonition:: Def.

 Metric `(d,E,F)`:math: is a map `d: E\times E \rightarrow F`:math: such that

 * `\forall p,q\in E\,, d(p,q)\geq 0`:math: (separation axiom)
 * `\forall p,q\in E\,, d(p,q) =0 \Rightarrow p=q`:math: (coincidence axiom)
 * `\forall p,q\in E\,, d(p,q) = d(q,p)`:math: (symmetry)
 * `\forall p,q,r\in E\,, d(p,q) \leq d(p,r) + d(r,q)`:math: (triangular inequality)


.. admonition:: Def.

 `(d,E,F)`:math: is a norm (metric induced by "normed" vector space) iff

 * `\forall p,q,r\in E\,, d(p,q) = d(p+r,q+r)\geq 0`:math:  (translation invariant)
 * `\forall p,q,\lambda\in E\,, d(\lambda p, \lambda q) = |\lambda|d(p,q)\geq 0`:math: (homogeneity)


Examples
--------



**E.g.**

* `d_1(p,q) = \| p-q\|_1 = \sum_{i=1}^n |p_i - q_i |`:math:
* `d_\infty(p,q) = \| p-q\|_\infty   = \max_{i=1..n} \{|p_i - q_i |\}`:math:
* `d_2(p,q) = \| p-q\|_2 = \sqrt{\sum_{i=1}^n (p_i - q_i)^2}`:math:

* *Weighted* `l_p`:math: *metric:* `d_p(p,q) =   \| p -q\|_p = \left ( \sum_{i=1}^n w_i|p_i-q_i |^p \right )^{\frac{1}{p}}`:math:


l_p metrics Illustration
------------------------


.. image:: _static/images/DT/metrics.*
     :width: 100%



Discrete Metrics
----------------

**Definition**

* We focus on triplets `(d,\mathbb{Z}^n,\mathbb{Z})`:math:

**Hence**

* `d_1`:math:, `d_\infty`:math: are Discrete Metrics
* `d_2`:math: is not a discrete metric
* `d_2^2`:math: is not a  metric
*  `\lceil d_2 \rceil`:math: is a discrete metric
*  `\lfloor d_2 \rfloor`:math: is a not discrete metric
*  `[d_2]`:math: is not a  metric


*Hints for last two results* use `p(2,3)\, q(-1,-1)\, r(0,0)`:math: and  `p(1,1)\, q(-1,-1)\, r(0,0)`:math:


Chamfer Mask
------------


**Weigthed vector**

   .. math::
      M = (\vec{v},\omega)

**Chamfer Mask**

Set of weighted vector

   .. math::
      \mathcal{M} = \{ M_i\in \mathbb{Z}^n\times \mathbb{N}^*\}_{1\leq i \leq m}


* with central symmetry
* which contains at least a basis of `\mathbb{Z}^n`:math:


Usually, chamfer masks are *G-symmetric*, i.e. restricted to

    .. math::
      \mathcal{M} = \{ M_i\in \mathcal{G}\times \mathbb{N}^*\}_{1\leq i \leq m}

with

    .. math::
      \mathcal{G} = \{ (x_1,\ldots,x_n)\in\mathbb{Z}^n\,|\, x_n\geq \ldots \geq x_1\geq 0 \}


Chamfer Distances
-----------------

**Chamfer path**

`k`:math:-Path based on vectors from a chamfer mask

  .. math::
       \mathcal{P} =\{ \alpha_1\vec{v}_{i_1}, \ldots, \alpha_k \vec{v}_{i_k} \}


**Length of a chamfer path**

  .. math::
      d_\mathcal{M}(\mathcal{P}) = \sum_k \alpha_k\omega_{i_k}


**Chamfer distance**

    Minimal length of chamfer path between `p`:math: and `q`:math:

*All chamfer distances induced distances, not necessarily norm*


Simple examples
---------------

**Path based distance**

    .. image:: _static/images/DT/chamferVect.*
          :width: 50%

**Matrix representation** for masks

`\mathcal{M}_{ab}=\{ (a,(0,1)^T) , (b,(1,1)^T) \}`:math:,  `\mathcal{M}_{abc}=\{ (a,(0,1)^T) , (b,(1,1)^T), (c,(2,1)^T)\}`:math:

      .. image:: _static/images/DT/chamfer2.*
         :width: 40%

For example:

    .. math::
      \mathcal{M}_{3,4} = \{ (3,(0,1)^T), (4,(1,1)^T) \}

(distances must be divided by 3 at the end)

Chamfer balls
-------------

  .. image:: _static/images/DT/cha2d-9boules.*
        :width: 100%



`\Rightarrow`:math: **We need constraints on** `\{\omega_i\}`:math: **to induce norms**


e.g.

   .. math::
      0 < a \leq b \leq 2a

   .. math::
      0 < 2a \leq c \leq a+b\quad\text{and}\quad 3b\leq 2c


Mask Construction
-----------------


**We construct the mask to approximate the Euclidean Metric**

* We first fix a set of vectors (usually, Farey fraction vectors in `\mathcal{G}`:math:)
* We find optimal weights to minimize the error (uniformly, average error, ...) with respect to `d_2`:math: on specific configuration

  * We minimize the error on the column `x=N`:math:
  * We minimize the error on the circle or radius `N`:math:

* We approximate optimal weights for integer numbers (plus scaling integer)


**Drawbacks**

* Just an approximation of the Euclidean metric
* Isotropic error distribution: error is maximized on specific orientations
* Increasing the mask size reduces the errors but increases the computational cost


Distance Transformation algorithm with Chamfer Masks
----------------------------------------------------

**Propagation using Dijkstra's algorithm**

* Implicitly construct a regular graph from `\mathbb{Z}^n`:math: vertices and edges taken from `\mathcal{M}`:math:
* Use Dijkstra's like algorithm to propagate distances from background points

`\Rightarrow`:math: *Computation cost in* `O(mn\log n)`:math: for `n`:math: grid points and `|\mathcal{M}|=m`:math:


.. list-table::
     :widths: 40, 20, 40

     * - .. image:: _static/images/DT/chamferGraphDom.*
             :width: 80%
             :align: center


       - .. image:: _static/images/DT/chamferMask.*
             :width: 100%
             :align: center


       - .. image:: _static/images/DT/chamferGraph.*
             :width: 100%
             :align: center


Raster Scan Algorithm
---------------------

Split the mask into two sub-masks and perform forward/backward scans with "min" operations.

  .. image:: _static/images/DT/chanfDT.*
         :width: 100%

Init
  .. math::
      DT(p) = 0 \quad \text{if} \quad p\not\in X\\
      DT(p) = +\infty \quad \text{if} \quad p\in X

Then
  .. math::
    DT(p) = min( DT(p), min_{(\omega_i,\vec{v}_i) \text{ in sub-mask}} ( DT(p+\vec{v}_i) + \omega_i ))

`\Rightarrow`:math: *Computational cost in*  `O(nm)`:math:

Other path-based distances
--------------------------


**Neighborhood sequence**

* We consider a sequence of Chamfer masks `\mathcal{M}_i`:math:
* At each step in the path construction, we consider another mask  `\mathcal{M}_i\rightarrow \mathcal{M}_{i+1}`:math:
* *Idea* each mask has directional error, changing masks reduce the error propagation


**Example**

"Octogonal" distance with infinite sequence `\{ d_1, d_\infty, d_1,\ldots, \}`:math:

Sometimes, explicit forms exist

  .. math::
    d_{oct}(p,q)=\max \left \{ \left \lfloor\frac{2}{3} d_1(p,q) + 1\right\rfloor, d_\infty(p,q)  \right\}


* Bit more difficult to ensure that a sequence/weighted sequence induce a metric



Euclidean metric
----------------

**Idea**

Still consider `(d,\mathbb{Z}^n, \mathbb{R})`:math: distances but with  integer based representations and algorithmic

**E.g.**

* Represent `d_2(p,q)\in\mathbb{R}`:math: by `d_2^2(p,q)\in \mathbb{Z}`:math:

* Represent `d_2(p,q)\in\mathbb{R}`:math: by vector `(p,q)^T\in \mathbb{Z}^2`:math:

* Similarly, `d_p(p,q)\in\mathbb{R}`:math:  by  `d_p^p(p,q)\in \mathbb{Z}`:math: or even  `(p,q)^T\in \mathbb{Z}^2`:math: for `l_p`:math: metrics



*Nice but are there fast algorithms for such exact metrics ?*


Separable Approach For Squared Euclidean Distance Transform
-----------------------------------------------------------

**We want to compute** (for all `p\in X`:math:)

   .. math::
       DT_2(p) = \min_{q\in\bar{X}} \{ d_2(p,q)\} =\sqrt{ \min_{q\in\bar{X}} \{ (p_1 - q_1)^2 + (p_2 - q_2)^2\}}
   .. math::
       DT_2(p) = \sqrt { \min_{q\in\bar{X}} SEDT(p) }


**Separable approach with intermediate map**

     .. math::
          g( i,j) =  \min_{x} \{ (x-i)^2\}

     .. math::
          SEDT( p(i,j) ) =  \min_{y} \{  (y-j)^2 + g(i,y)\}

in dimension 3, we would have

     .. math::
          g(i,j,k) = \min_x \{(x-i)^2 \},   h(i,j,k) = \min_y \{(y-j)^2 + g(i,y,k) \}\\
          SEDT( p(i,j,k) ) =  \min_{z} \{  (z-k)^2 + h(i,j,z)\}


First Step
----------

**Simple two-scan propagation**

 .. image:: _static/images/DT/saitoX.*
        :width: 80%




`\Rightarrow`:math: `O(N^2)`:math: **in 2D for NxN image**

`\Rightarrow`:math: `O(N^d)`:math: **in d-D for N^d image**




Second Step
-----------

`g( i,j) =  \min_{x} \{ (x-i)^2\}`:math: and `SEDT( p(i,j) ) =  \min_{y} \{  (y-j)^2 + g(i,y)\}`:math:

 .. image:: _static/images/DT/edt_saito.*
       :width: 100%


**Key-point** Lower envelope computation of a set of parabolas

Lower Envelope Computation
--------------------------

Consider the set of parabolas `\{  (x-k)^2 + g_k \}_{k=1\ldots N}`:math:


 .. image:: _static/images/DT/edt_para.*
       :width: 60%


* Any two parabolas have single point intersection
* For lower envelope computation, the intersection point acts as a *pivot*

  * If `P_k`:math: and `P_{k'}`:math: are two parabolas with intersection `q`:math: and `k<k'`:math:
  * `P_k`:math: cannot appear in the lower envelope for abscissa greater than `q`:math:

`\Rightarrow`:math: **Lower envelope computation in** `O(N)`:math: **using stack based approach ;)**





Overall SEDT Algorithm
----------------------

Given a `N^d`:math: image

**Algorithm**

* First Step: perform two-scan propagation
* For all `(d-1)`:math: remaining dimensions: compute independent lower envelope which are in `O(N)`:math:

`\Rightarrow\quad O(d\cdot N^d)`:math: *algorithm for error free Euclidean metric DT*



.. list-table::

  - * .. image:: _static/images/DT/neigeDT_508_p.*
          :width: 60%
          :align: center

    * .. image:: _static/images/DT/AlCaponeDistanceMap.*
          :width: 60%
          :align: center


Generalizations
---------------

**Thanks to separability**

* We have independent 1D problem to solve
* Synchronization steps only occurs when we go to the next dimension

**Optimal multi-thread implementation**

  .. image:: _static/images/DT/edt_multithread.*
     :width: 80%


**Generalization to toric domains**

  .. image:: _static/images/DT/edt_tore.*
     :width: 80%

*Useful to characterize periodic structures in arbitrary dimensions*


Generalization to other metrics
-------------------------------

**Principle**

* Separable decomposition works for any metric satisfying the *monotonicity* property:

.. admonition:: Def.

   We consider `p(x,y)`:math:, `q(x',y')`:math:  with `x<x'`:math:

   `r( x'',O)`:math: be a point on the x-axis such that `d(p,r) = d(q,r)`:math:

   Let  `s(u,0)`:math: be another point on the x-axis
   A metric `d`:math: is *monotonic* if

    .. math::
       u < x'' \implies d(p,s) \leq d(q,s)

    .. math::
       u > x'' \implies d(p,s) \geq d(q,s)



**Result**

* All `l_p`:math: metrics are monotonic
* All Chamfer masks induced by norms are monotonic
* All path based distances inducing norms with axis-symmetric unit ball are monotonic


`\Rightarrow`:math: **Let's use the separable approach for other metrics !**


Voronoi Diagram
---------------

**Definition**

Given a set of sites  `S=\{ s_i\in \mathbb{R}^d\}`:math:, the *Voronoi Diagram* is a decomposition of the space into closed cells `{c_i}`:math: such that
    .. math::
        Voro_{S}(s_i) = \{ x\in\mathbb{R}^d,\, d(x,s_i) \leq d(x,s_j),\, \forall s_j\in S\}

Each cell can be further decomposed into sub-dimensional i-facets taking into account cases where  `d(x,s_i)= d(x,s_j)`:math:


  .. image:: _static/images/DT/voronoi_diagramme.*
       :width: 30%




**Voronoi Diagram** `\equiv`:math: **Distance Transformation**


    .. math::
        DT(p)  = d(p,q)\, \text{ with } q\in\bar{X}\text{ such that }p\in Voro_{\bar{X}}(q)



`\Rightarrow`:math: *Getting the distance value is equivalent to localizing a point in a Voronoi diagram*



Separable Voronoi Map
---------------------

Input set: `X\subset\mathbb{Z}^2`:math:, we construct `Voro_{\bar{X}}\cap\mathbb{Z}^2`:math:

 .. image:: _static/images/DT/Voromap-random-orig.*
       :width: 70%




Separable Voronoi Map
---------------------

.. list-table::

 * - .. image:: _static/images/DT/Voromap-random-diag.*
         :width: 100%

   - .. image:: _static/images/DT/Voromap-random.*
         :width: 100%

   - .. image:: _static/images/DT/Voromap-random-hue.*
         :width: 100%

 * - .. image:: _static/images/DT/Voromap-random-diag-complete.*
         :width: 100%

   - .. image:: _static/images/DT/Voromap-random-complete.*
         :width: 100%

   - .. image:: _static/images/DT/Voromap-random-hue-complete.*
         :width: 100%


Generic Algorithm
-----------------

**Main Result**

.. list-table::
     :widths: 70 , 11, 19

     * - For any monotonic metric and an image `[1\ldots n]^d\rightarrow \{0,1\}`:math:, the Voronoi Map (and the distance transformation) can be obtained by the *separable algorithm* in `O( d\cdot n^d\cdot (C + H) )`:math:

       - .. image:: _static/images/DT/closest.*
             :width: 100%

       - .. image:: _static/images/DT/hiddenBy.*
             :width: 100%

* **C**: Closest(u,v, p), decide whether u or v is closest to p
* **H**: HiddenBy(u,v,w, 1D-line), decide if Voronoi cells of u and w *hide* the Voronoi cell of v  on the 1D-line

+-------------------+--------------------+------------------------+------------------------------------------+
|Metric             | C                  | H                      | Total                                    |
+===================+====================+========================+==========================================+
|`l_2`:math:        | `O(1)`:math:       | `O(1)`:math:           | `\Theta(d\cdot n^d)`:math:               |
+-------------------+--------------------+------------------------+------------------------------------------+
|`l_1`:math:        | `O(1)`:math:       | `O(1)`:math:           | `\Theta(d\cdot n^d)`:math:               |
+-------------------+--------------------+------------------------+------------------------------------------+
|`l_\infty`:math:   | `O(1)`:math:       | `O(1)`:math:           | `\Theta(d\cdot n^d)`:math:               |
+-------------------+--------------------+------------------------+------------------------------------------+
|Exact `l_p`:math:  | `O(log(p))`:math:  |`O(log(p).log(n))`:math:| `O(d\cdot n^d\log(p)\cdot\log(n))`:math: |
+-------------------+--------------------+------------------------+------------------------------------------+
|Chamfer Norms      | `O(log(m))`:math:  |`O(log^2(m))`:math:     | `O(d\cdot n^d\cdot\log^2(m))`:math:      |
+-------------------+--------------------+------------------------+------------------------------------------+
|Neigh. Seq. Norms  | O(1)               |`O(\log(n))`:math:      | `O(d\cdot n^d\cdot\log(n))`:math:        |
+-------------------+--------------------+------------------------+------------------------------------------+



Examples
--------


   .. list-table::

      * - .. image:: _static/images/DT/Voromap-huesimple.*
              :width: 80%
        - .. image:: _static/images/DT/Voromap-hue-l6-simple.*
              :width: 80%

      * - `l_2`:math:

        - `l_6`:math:

Path based Metrics
------------------


**Better expected bounds for path based norms**

+---------------------+---------------------+-------------------------+------------------------------------------+
|Metric               | C                   | H                       | Total                                    |
+=====================+=====================+=========================+==========================================+
|Chamfer with adapter | `O(m)`:math:        |`O(m\cdot log(m))`:math: | `O(d\cdot m\cdot n^d\cdot\log(n))`:math: |
+---------------------+---------------------+-------------------------+------------------------------------------+
|**Chamfer Norms**    | `O(\log(m))`:math:  |`O(\log^2(m))`:math:     | `O(d\cdot n^d\cdot\log^2(m))`:math:      |
+---------------------+---------------------+-------------------------+------------------------------------------+

Similar expected results for neighborhood sequences




Examples
--------


   .. list-table::

      * - .. image:: _static/images/DT/Voromap-huesimple.*
              :width: 80%
        - .. image:: _static/images/DT/Voromap-hue-l6-simple.*
              :width: 80%

      * - `l_2`:math:

        - `l_6`:math:



Subquadratic Algorithm for path based distances
===============================================


Path Based Metric and Rational balls
------------------------------------

**Notations**

* Chamfer masks: `\mathcal{M} = \{ (\vec{v}_i,\omega_i) \in \mathbb{Z}^n\times \mathbb{N}^*\}_{1\leq i \leq m}`:math: (we consider only chamfer masks inducing norms)

* Rational ball: `\mathcal{B}_{\mathcal{M}} = Conv\left ( \{
  \frac{\vec{v}_i}{\omega_i} \} \right )`:math: [Normand, Strand,...]

* Rational ball faces have normal vector `\mathcal{F}_i`:math:

   .. image:: _static/images/DT-chamf/ratball.*
         :width: 50%


`\mathcal{M}_{7,8,11,14}`:math:

Distance Evaluation
-------------------

**[Normand et al.]**


   .. math::
        d(O,p) = \max_i \{ \mathcal{F}_i\cdot \vec{Op}\}

`\Rightarrow`:math: `O(m)`:math:



Can be generalized to other path based distances to get similar expression

   .. math::
        d(O,p) = \max_i \{ f_i(\mathcal{F}_i\cdot \vec{Op}) \}

for some function `f_i`:math: (based Lambek-Moser inverse sequences)

   .. image:: _static/images/DT-chamf/seqDT.*
         :width: 80%


Optimized Distance Evaluation
-----------------------------


**Computational Geometry setting**

* The facet inducing the `\max`:math: is given by the facet pierced by the straight line `(Op)`:math:

* `\Rightarrow`:math: *Ray shooting problem in convex polytopes*


**Fast Distance computation**

* Following [Matousek and Schwarzkpof]


    `\Rightarrow`:math:  `O(m^{\lfloor d/2\rfloor})`:math: space/pre-processing and `O(\log m)`:math: per query



Separable Predicates for Chamfer Masks
--------------------------------------


**Goal**

* If we could have predicates in `O(h)`:math: then we have exact Voronoi Map/DT in `O(d\cdot h\cdot n^d)`:math:
* Raster scan is in `O(m\cdot n^d)`:math:


**Main Result**

   .. math::
        h = O(\log^2m)


*==> First sub-quadratic DT algorithm for Chamfer metrics*


Dimension 2
-----------

**Key point**

* Given to points and a straight line, detect the position of the Voronoi edge on the line

* we are looking for point `r\in l`:math: such that `d_\mathcal{M}(p,r) = d_\mathcal{M}(q,r)`:math:


   .. image:: _static/images/DT-chamf/initialproblem.*
       :width: 40%


Warm up: Localizing a point
---------------------------

**Question** Find the *cone* at `p`:math: containing a point `r`:math:


*==> Dichotomic/Binary search* (thanks to convexity of the metric)

*==>* `O(\log m)`:math:


   .. image:: _static/images/DT-chamf/searchPoint.png
       :width: 60%



Algorithm Overview
------------------

**Idea**

If we have *localized* the Voronoi edge point, we are done (find the exact position given by linear system with one unknown)



   .. image:: _static/images/DT-chamf/algoEnd.png
       :width: 60%







Step 1: Shrinking `\mathcal{M}_p`:math:
---------------------------------------

.. code-block:: c

   ShrinkMp( Mp, Mq )

      if |Mp| == 1
        return the cone in Mp
      else
        Split cones Mp -> { Mp, cone, M-} with |M+|~|M-|
        {v1,v2} = cone
        dp1 = distance d_M(p, v1 intersection l)   //O(1)
        dp2 = distance d_M(p, v1 intersection l)   //O(1)
        dq1 = localize and get the distance of d_M(q, v1 intersection l) //O(log(m))
        dq2 = localize and get the distance of d_M(q, v2 intersection l) //O(log(m))

        c1  = closest point between p and q at v1
        c2  = closest point between p and q at v2

        if (c1 == c2 == GREEN)
         return ShrinkMp(M+)

        if (c1 == c2 == BLUE)
         return ShrinkMp(M-)

         return cone


*Correctness*

* Chamfer norm implies 2  connected sets (blue/green), maybe overlapping
* When evaluating distance on the line, the function is convex (-> orientation)

Step 2: Shrinking `\mathcal{M}_q`:math: and final computation
-------------------------------------------------------------

**Shrinking** `\mathcal{M}_q`:math:

* Similar algorithm
* Can be speed-up using `\mathcal{M}_p`:math: cone
* `\Rightarrow O(\log^2 m)`:math:


**Final step**

* Small computation in each cone
* `\Rightarrow O(1)`:math:


Fast computations in higher dimensions
--------------------------------------


**Basic Idea** for `\mathcal{M}`:math: in `\mathbb{R}^d`:math:

* Each  `{p,l}`:math: `{q,l}`:math: defines a plane (`P_{pl},\, P_{ql}`:math:)
* `\mathcal{B}_\mathcal{M}\cap P_{pl}`:math: induces a 2-dimensional polytope


* `\Rightarrow`:math: *2D problem* with `O(\log^2 m)`:math: computational cost



**Conclusion**

* Closest() and HiddenBy() predicates can be implemented in `O(\log^2m)`:math:

* Exact Voronoi map/Distance transformation of Chamfer norms using separable approach in

    .. math::
          O(d\cdot \log^2 m\cdot n^d)


   .. image:: _static/images/DT-chamf/nDto1D.*
            :width: 50%


Reverse Distance Transformation
===============================

Reverse Transformation
----------------------

**Problem setting**

.. admonition:: Def.

 Given a *metric* `(d,E,G)`:math: and a set of balls `\mathcal{B}=\{ B_i=(p_i,r_i)\in E\times G\}_{i=1\ldots N}`:math:, reconstruct the binary shape `X`:math:

   .. math::
       X = \bigcup_{i=1\ldots N} B_i

**Why?**

* Reverse operation of the Distance Transformation

    .. math::
       \text{If }   \mathcal{B}=\left \{(p,DT(p))\, \forall p\in X\right \}, \text{ then } RDT( \mathcal{B} ) = X

* To reconstruct the shape `X`:math: if we characterize it as a union of balls (e.g. via *medial axis*)


**Bruteforce approach**

For `n\times m`:math: image

  .. math::
       O(Nnm)


Separable Approach for `l_2`:math:
----------------------------------

W.l.o.g. we consider `d=2`:math:

Let us denote `p_k=(x_k,y_k)`:math: for `k=1\ldots N`:math:, then

  .. math::
       X = \left \{ (i,j)\,|\, \exists k\in[1,N] \, (i - x_k)^2 + (j-y_k)^2 \leq r_k^2\right \}

Which can be rewritten

  .. math::
     X =\left \{ (i,j)\,|\, \max_{k=1\ldots N}\{ r_k^2 -(i - x_k)^2 - (j-y_k)^2\} >0\right \}

`\Rightarrow`:math: **Separable decomposition**


Start from a map `f: \mathbb{Z}^2\rightarrow \mathbb{Z}`:math: with `f(x,y) = r_k^2`:math: if `((x,y),r_k)\in\mathcal{B}`:math: (`f(x,y) = 0`:math: otherwise)


     .. math::
          g(i,j) =  \max_{x} \{ f(x,j) - (x-i)^2\}

     .. math::
          REDT(i,j) =  \max_{y} \{g(i,y) -  (y-j)^2 \}


Illustration
------------

**Similar algorithm**

* Lower Envelope computation of parabolas `\rightarrow`:math: Upper envelope computation of a set of parabolas
* Generalization of arbitrary dimension



.. image:: _static/images/DT/redt-example.*
   :width: 80%
   :align: center

.. image:: _static/images/DT/redt_para.*
   :width: 40%
   :align: center



`\Rightarrow`:math: `O(d\cdot n^d)`:math: **separable algorithm for REDT**


Associated Structure from Computational Geometry
------------------------------------------------

**Voronoi map --> Power map**

* Kind of Voronoi diagram with additive power metric. For example the power of a point x w.r.t. ball `(s,r)\in\mathbb{R}^d\times\mathbb{R}`:math:

     .. math::
        \pi(x,(s,r)) = d^2(x,s) - r^2

.. admonition:: Def.

  Given a set of *weighted* sites `S=\{ (s_i,w_i)\in \mathbb{R}^d\times\mathbb{R}\}`:math:, the *Power Diagram* is a decomposition of the space into closed cells `{c_i}`:math: such that
    .. math::
        Power_{S}((s_i,w_i)) = \{ x\in\mathbb{R}^d,\, \pi(x,(s_i,w_i)) \leq \pi(x,(s_j,w_j)),\, \forall (s_j,w_j)\in S\}



Each cell can be further decomposed into sub-dimensional i-facets taking into account cases where  `d(x,s_i)= d(x,s_j)`:math:


.. list-table::

 * -  .. image:: _static/images/DT/Power_diagram.*
         :width: 50%
         :align: center

   - .. image:: _static/images/DT/Radical_axis_intersecting_circles.*
         :width: 40%
         :align: center

Power Map
---------

**Idea**

* REDT of a set of balls `\mathcal{B}`:math: *is equivalent* to the construction of `\left(Power_{\mathcal{B}}\cap\mathbb{Z}^d\right )`:math:


**Results**

* The separable algorithm for monotonic metrics can be extended to generate `\left(Power_{\mathcal{B}}\cap\mathbb{Z}^d\right )`:math:
* `O( d\cdot n^d\cdot (C + H) )`:math: **computational cost  for a large class of metrics**



Medial Axis Extraction
======================

Problem Description
-------------------

**Alternative Definitions**

* Self intersection of wavefronts in prairie model  (`\rightarrow`:math: PDE fromulation)
* Center of maximal balls contained in the shape
    `B`:math: is maximal in X if `\not\exists B'\subset X,\, B\subset B'`:math:
* Set of balls touching `\partial X`:math: at least twice
* 1D topological equivalent of the contour
* ...



.. list-table::

 * -  .. image:: _static/images/DT/grass.*
         :width: 100%
         :align: center

   - .. image:: _static/images/DT/am-cercles.*
         :width: 100%
         :align: center

Contact Points based Geometrical Definition
-------------------------------------------

**Voronoi Based Approximation**


   Shape `\Rightarrow`:math: Point set approximation `\Rightarrow`:math: Voronoi Diagram `\Rightarrow`:math: Medial Axis approximation



.. image:: _static/images/DT/approxma.*
    :width: 70%
    :align: center


*Convergence results exists for various classes of Voronoi based medial axis*


Maximal Ball based Definition
-----------------------------

.. admonition:: Def.

     A  *maximal ball* is a ball contained in the shape not entirely covered
     by another ball contained in the shape

.. admonition:: Def.

     The *medial axis* of a shape is the set of maximal ball centers
     contained in the shape.

**Digital Setting**

* `X\subset\mathbb{Z}^d`:math:
* We consider digital balls `B\cap\mathbb{Z}^d`:math:

* `\Rightarrow`:math: *Finite set of digital  balls contained in* `X`:math:
* `\Rightarrow`:math: Medial Axis Extraction `\equiv`:math: *Combinatorial Covering problem*


**Reversible Encoding of X**

  .. math::
         X = \bigcup_{B_i\in MA(X)} B_i



DT and Digital Medial Axis
--------------------------

**DT as preliminary step**

Given `p\in X`:math: and `r\in\mathbb{R}`:math: such that Euclidean ball with `B(p,r)\cap X\in X`:math:, we have

   .. math::
        B(p,r) \subseteq B(p, DT(p))


(defined for `l_2`:math: but trivial generalizations to other metrics)



.. list-table::

 * - .. image:: _static/images/DT/2spheres_edt_surf.*
         :width: 100%

   - .. image:: _static/images/DT/carre_edt_surf.*
         :width: 100%

   - .. image:: _static/images/DT/homme_edt_surf.*
         :width: 100%



`\Rightarrow`:math: *Set of candidate balls* `O(|X|)`:math:






Digital Ball vs. Euclidean Balls
--------------------------------

**Covering Test**


Let us consider a *IsCoveredBy(B,B')* a predicate returning true if `B\subseteq B'`:math:



* If B and B' are *Euclidean balls* `\Rightarrow`:math: The predicate is in  `O(1)`:math:

* If B and B' are *Digital balls* `\Rightarrow`:math: The predicate is in  `O(\max(|B|,|B'|))`:math:


     `B\subset B'`:math: `\Rightarrow`:math: `(B\cap\mathbb{Z}^2)\subset (B'\cap\mathbb{Z}^2)`:math:

but


     `B\subset B'`:math: `\not\Leftarrow`:math: `(B\cap\mathbb{Z}^2)\subset (B'\cap\mathbb{Z}^2)`:math:



`\Rightarrow`:math: *Bruteforce Digital Medial Axis Extraction* `O(|X|^2r^2_{max})`:math: (with `r_{max}`:math: the maximal DT value)


Implementing IsCoveredBy()
--------------------------

**Goal**

Design  a *IsCoveredBy()* predicate with cost as a function of `m`:math:


**Elementary Chamfer Masks** `\mathcal{M}\in\{d_1, d_\infty\}`:math:

  .. math::
        (p,DT(p)) \in MA \Leftrightarrow DT(p+\vec{v}) < DT(p) + \omega,\, \forall (\vec{v},\omega)\in\mathcal{M}


Also true for `\mathcal{M}_{3,4}`:math: with the following rewriting rules of the DT map:

* `3 \rightarrow 1`:math:
* `6 \rightarrow 5`:math:


**Other path-based distances:** Look-up table approach

* We pre-compute
    .. math::
        Lut(\vec{v},r) =\min \{ r'\,|\, B(O,r)\subseteq B(O+\vec{v},r'\}

* Then,
    .. math::
        (p,DT(p)) \in MA \Leftrightarrow DT(p+\vec{v}) < Lut(\vec{v},DT(p)),\, \forall \vec{v}\in\mathcal{V}

`\mathcal{V}`:math: is the neighborhood test.

*Bottlenecks* Efficient computation of Lut, bounds on `|\mathcal{V}|`:math:, bounds on `|Lut|`:math:, ...


Global approach using Power Map
-------------------------------

**Idea**

Get the Medial Axis as a by-product of the Power map


.. admonition:: Lemma

  Let `S\subset \mathbb{R}^d\times\mathbb{R}`:math: and `X=\bigcup_{B_i\in S} B_i`:math:

   .. math::
        B\subset B' \implies    Power_{S}(B) \cap X = \emptyset


*Non-empty power map cells are related to maximal balls*


[Skipping details...]

`\implies`:math: *Separable algorithm to extract the medial axis*

`\implies`:math: `O( d\cdot n^d\cdot (C + H) )`:math: **computational cost  for a large class of metrics**


One algorithm to rule them all
------------------------------

.. list-table::

 * - .. image:: _static/images/DT/Al-orig.*
         :width: 100%
         :align: center

   - .. image:: _static/images/DT/Al-DT.*
          :width: 100%
          :align: center

   - .. image:: _static/images/DT/Al-RDMA.*
          :width: 100%
          :align: center

 * - .. image:: _static/images/DT/neige_254.*
         :width: 100%
         :align: center

   - .. image:: _static/images/DT/neige_254_DT.*
          :width: 100%
          :align: center

   - .. image:: _static/images/DT/neige_254_RDMA.*
          :width: 100%
          :align: center


Toward Minimal Medial Axis
--------------------------

**Question**

Is the set of maximal balls a minimal representation of X as union of balls ?

**Answer** No

* Maximal balls are defined by binary predicates `IsCoveredBy(B,B')`:math:
* A maximal ball B can be covered by union of balls, which makes B unnecessary in the representation of X


**Toward minimal MA**

.. admonition:: Thm.

  If we allow k-ary predicates `IsCoveredBy(B, S_k)`:math: with
  `|S_k|=k`:math: the minimal medial axis problem becomes
  *NP-complete*

Heuristics
----------

  .. image:: _static/images/DT/amOptHeuristics.*
      :width: 100%



.. |imp| replace:: `\Rightarrow`:math:



Topological Skeleton
====================


Introduction
------------


*Digital Medial Axis* is defined as a set of balls without any topological information

**We are thus looking for**

* a minimal subset of X (skeleton) with the *same topological structure*
* as far as possible, we would like the skeleton to be *centered*



|imp| **Iterative thinning via Simple Point Removal**



Simple Point
------------

.. admonition:: Def.

  A point `p\in X`:math: is simple for `X`:math: if  `X`:math: and `X\setminus\{p\}`:math: are in the same *homotopy equivalence class*


* In dimension 2, same number of connected components of the object and of its complementary
* In dimension 3, we must preserve holes/tunnels
* ...


Topological Transformations
---------------------------


**From Simple Point Definition**

Let `\phi`:math: by any sequence of insertions/removals of simple points, then `X`:math: and `\phi(X)`:math: are in the *same homotopy equivalence class*


.. image:: _static/images/DT/mug-torus.*
    :align: center


*How to characterize simple points ?*


`\alpha`:math:-simple points
----------------------------


**Definition**


.. admonition:: Def.

 A point `p\in X`:math: is `(\kappa,\lambda)`:math:-simple for `X`:math: if

 *   `X`:math: and `X\setminus\{p\}`:math: have the same number of `\kappa`:math:-components

 *   `\overline{X}`:math: and `\overline{X\setminus\{p\}}`:math: have the same number of `\lambda`:math:-components


**Example**

.. image:: _static/images/DT/pointsimple.*
     :width: 60%
     :align: center


*(which are resp. (0,1)- and (1,0)-simple ?)*


Local characterization
----------------------

**Main Results**

.. admonition:: Thm.

  In dimension 2 and 3, `(\kappa,\lambda)`:math:-simplicity of `p\in
  X`:math: *can be decided locally* at `p`:math:

(`3\times 3`:math: neighborhood in 2D, `3\times 3\times 3`:math:)

**E.g. 2D**

* `N^*_8(p)`:math::  8-neighborhood around `p`:math: (without p)
* `C_\kappa^p(X))`:math:: set of `\kappa`:math:-connected components in `X`:math: adjacent to `p`:math:
* `T_\kappa(p,X) = | C_\kappa^p(N^*_8(p)\cap X|`:math:


     |imp| `p\in X`:math: is `(\kappa,\lambda)`:math:-simple for `X`:math: `\Leftrightarrow`:math: `T_\kappa(p,X) =T_\lambda(p,\bar{X})=1`:math:


In dimension 3, `T_\kappa(p,X)`:math: definition is a bit more complex but still local


Illustration
------------

All configurations in 2D

.. list-table::

   * - .. image:: _static/images/DT/table8_4.*
           :width: 100%

     - .. image:: _static/images/DT/table4_8.*
           :width: 100%
   * - (0,1)

     - (1,0)


Homotopic thinning
------------------

**Idea**

Iterate until stability over sequential simple points removal |imp| *ultimate homotopic thinning*


.. list-table::

   * - .. image:: _static/images/DT/chrom_simples.*
           :width: 80%
           :align: center

     - .. image:: _static/images/DT/chrom_sk1.*
           :width: 80%
           :align: center

   * - .. image:: _static/images/DT/chrom_sk2.*
           :width: 80%
           :align: center

     - .. image:: _static/images/DT/chrom_sk3.*
           :width: 80%
           :align: center


In Dimension 3
--------------


   .. image:: _static/images/DT/a_skel_ult.*
       :width: 80%
       :align: center

Algorithm
---------


.. code-block:: c

    P = { p in X | p is simple for X }
    while ( P != empty )
       Q = emptyset
       for all points p in P
         if (p is simple for X)
           X = X \ {p}
           for all q in N(p)
              Q = Q + {q}

       P = emptyset
       for all points p in Q
         if (p is simple for X)
           P = P+ {p}



.. image:: _static/images/DT/chrom_ambi.*
     :width: 50%
     :align: center

Homotopic thinning with anchor points
-------------------------------------

**Idea**

Based on an Oracle, we decide to block some simple points during the thinning


**Generic algorithm**

Breadth first thinning if P is implemented as a queue

.. code-block:: c

    P = { p in X | p is simple for X }
    while ( P != empty )
       Q = emptyset
       for all points p in P
         if (p is simple for X) and (p is not anchor point)
           X = X \ {p}
           for all q in N(p)
              Q = Q + {q}

       P = emptyset
       for all points p in Q
         if (p is simple for X)
           P = P+ {p}


**E.g.**

p is anchor point if it has only one neighbor in X

Illustration
------------

.. list-table::

   * - .. image:: _static/images/DT/a_skel_cur.*
            :width: 100%

     - .. image:: _static/images/DT/a_skel_end.*
            :width: 100%


Curve or Surface based Skeleton
-------------------------------

**Idea**

Anchor points can be specified to generate surface based skeleton

.. list-table::

   * - .. image:: _static/images/DT/torus_skelsur2.*
            :width: 100%

     - .. image:: _static/images/DT/torus_skelsur3.*
            :width: 100%


Misc.
-----

**Guided Thinning**

Instead of using a queue for P, we consider a *priority list  with distance transformation values*

|imp| Better geometry  (central axis) of the skeleton


**Parallel thinning**

* Sequential algorithm needs to test the simplicity twice
* Idea of parallel thinning: we mark some simple points and remove them in parallel

  * We add constraints on simple points to allow parallel removal
  * Orientation based process (N,S,W,E)

|imp| usually, parallel thinning algorithms are more efficient and provide centered skeletons


**Active works**

* Extensions to grayscale images
* Optimize the simplicity test (binary decision tree, ...)
* Definition of simple point sets to allow more efficient parallel removal
* Definition of simple structures in topological cellular spaces
* ...

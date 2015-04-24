==================================
Digital Geometry: Contour Analysis
==================================
:author: David Coeurjolly




Contour representation
======================


Contour Encoding
----------------

**Objectives**

* *Compression* : compression ratio between the contour and its code
* *Reversibility* : from the encoding, we could reconstruct the contour (loss-less compression)
* *Robustness* : invariant with respect to a given class of transformations
* *Information capacity* : can geometrical or topological information be deduced from the code


Freeman Chain Code
------------------


**Idea**

Starting point + differential code according to adjacency displacement and an orientation


  .. image:: _static/images/freeman.*
      :width: 100%


  .. image:: _static/images/codage_freeman.*
      :width: 100%

Example
-------



  .. image:: _static/images/codage_freeman_bis.*
      :width: 100%



  .. math::
       P_0=(2,1),\, C=\{2,1,0,1,0,7,7,6,5,4,3,5,4,3\}


Properties
----------

**Reversible** and **unique** encoding

**Code driven geometrical transformations**

- Translation: just move `P_0`:math:
- Rotations by multiple of `\frac{\pi}{2}`:math: `\quad c'_i = c_i+2\, mod(8)`:math: (for (0)-adjacency)

**Basic length estimator**

- `L += 1`:math: for even codes
- `L +=\sqrt{2}`:math: for odd codes

Properties (Ctd.)
-----------------

Given a (1)-adjacency, let `n_i`:math: be the number of ith-code

**Path is closed iff**
    .. math::
         n_i = n_{i+2\,mod(4)}

(but may be self-intersecting)


**Representation as a word on an alphabet**

`W=\{a,b,\bar{a},\bar{b}\}`:math:

* Closed path: words such that number of a equals number of `\bar{a}`:math: ...
* Let suppose that `\bar{(u\cdot v)} = \bar{v}\cdot \bar{u}`:math:


.. rst-class:: roundedquote

     A Polyomino `P`:math: tiles the plane if and only if its contours has the following structure (up to cyclic rotations)      `X\cdot Y\cdot Z\cdot \bar{X}\cdot \bar{Y}\cdot \bar{Z}`:math: [Beauquier-Nivat]


   .. image:: _static/images/nivat.*
     :width: 40%
     :align: center



Fundamendal Objets: DSS
========================





Digitization based definition
-----------------------------

Given a digitization model:


.. admonition:: Def.

     A digital straight line (resp. segment) is the result of a digitization and an Euclidean line (resp. segment)



First Historical Construction
-----------------------------

**Digital Segment tracing by Bresenham's algorithm**

GIQ based definition: For each abscissa we consider the closest grid point

   .. image:: _static/images/bresenham.*
       :width: 100%
       :align: center


**Incremental construction**

* Process the abscissa one by one
* Propagate errors

**Properties**

* The digitization is a (0)-arc (proof it)
* If slope is in [0,1], only two codes occur


Implementation details
----------------------

Segment between `(x_1,y_1)`:math: and `(x_2,y_2)`:math: in `\mathbb{Z}^2`:math: with slope in [0,1]

**Naive approach**

.. code-block:: c

    y = y_s
    for(i = x_1; i <= x_2; ++i)
       display(i,y);
       y_real = (y_2-y_1)/(x_2-x_1) * (i+1) + y_1;
       dy = y_real - y;
       if ( dy > 0.5)
         y++;


* Mix between integers (i,x_s,x_e,y_prev) and real (y,dy) numbers
* 6 operations on real numbers + comparison

Integer only implementation
---------------------------



.. code-block:: c

    e = x_2 - x_1
    dx = 2*e
    dy = 2*(y_2 - y_1)
    while (x_1 < x_2)
      display(x_1,y_1);
      x_1 ++;
      e  -= dy;
      if (e <= 0)
         y_1 ++;
         e += dx:


**Rationale**

* Error e can be propagated when moving to the next point (by an increment given by the slope)
* Instead of computing the slope, we keep its numerator/denominator
* To handle 0.5 numbers, we multiply everything by 2
* `\Rightarrow`:math:  inside the loop, 4 integer based operations and one comparison, no possible round-off errors

First arithmetical results
--------------------------

Let us consider GIQ digitization scheme (similar to Bresenham's) and a straight line `y=ax +b`:math: with `0\leq a \leq 1`:math:. Let `S`:math: be the digitization of the straight line and `C` its Freeman code


.. admonition:: Thm

       .. math::
            \exists p,q\in\mathbb{Z}, a=\frac{p}{q} \Leftrightarrow\text{ C is periodic with minimal period  }  \frac{q}{gcd(p,q)}



*<demo>*


  .. image:: _static/images/bresenham2.*
      :width: 50%
      :align: center


Example
-------


  .. image:: _static/images/exemple_droite.*
     :width: 70%
     :align: center


Periodic structure `\rightarrow`:math: canonical pattern

* Fast drawing algorithms (run-based, pattern-based, ...)
* Fast recognition algorithms
* ...


Euclid's  Axioms
----------------

**Any two points  define a unique straight line**

.. list-table::

 * - .. image:: _static/images/euclide1.*
          :width: 60%
   - .. image:: _static/images/euclide2.*
          :width: 60%




**Two non-parallel straight lines intersects at a single point**

.. list-table::

 * - .. image:: _static/images/ex_inter_1_pt.*
          :width: 20%
   - Single point

 * - .. image:: _static/images/ex_inter_vide.*
          :width: 20%
   - Empty set

 * - .. image:: _static/images/ex_inter_non_connexe.*
          :width: 50%
   - Non-connected set

 * - .. image:: _static/images/ex_inter_connexe.*
          :width: 35%
   - Connected set



Euclid's  Axioms (bis)
----------------------


`\Rightarrow`:math: we need to redefine parallelism, intersections, ...


Switching to another digitization scheme, we may avoid some situations.

E.g. with analytical models, empty set case will never occur


DSS Characterizations
---------------------

**Chordal Property** [Rosenfeld]

.. admonition:: Def.

  .. math::
     \forall p \forall q\text{ and }\forall m\in[pq]\text{, there exists M(i,j) such that }\max(|i-x|,|j-y|)<1



  .. image:: _static/images/corde.*
      :width: 30%
      :align: center

**Evenness Property** [Veelaer]

.. admonition:: Def.

  .. math::
     \forall a,b,c,d\in[pq] \text{ such that }\vec{ba}_x=\vec{dc}_x,\, |\vec{ba}_y-\vec{dc}_y|=1




  .. image:: _static/images/evenness_prop.*
      :width: 50%
      :align: center


Diophantine Equations
---------------------

**Definition**

.. admonition:: Def.

    Diophantine equation = Equation with integer parameters and solutions in `\mathbb{Z}`:math:


**Example**

  .. math::
       ax + by = c

(with `a,b,c\in\mathbb{Z}`:math: )

*What is the general form of solutions of such linear diophantine equation ?*


Solving Linear Diophantine Equation
-----------------------------------

`ax + by = c`:math:, and let `S`:math: denote the solutions


**Existence**

   .. math::
       S\neq\emptyset \Leftrightarrow gcd(a,b) | c

**Homogeneous case**

    .. math::
        ax+by=0 \Rightarrow S=\{(-bk,ak), k\in\mathbb{Z}\}


**General case**

`a' = \frac{a}{gcd(a,b)},\, b'=\frac{b}{gcd(a,b)},\, c'=\frac{c}{gcd(a,b)}`:math:

    .. math::
      a'x + b'y = c'

Since `gcd(a',b')=1`:math:, `\exists u,v\in\mathbb{Z}`:math: such that `a'u +b'v = 1`:math: [Bezout]


  .. math::
       \Rightarrow S=\{(uc' - b'k, vc' + a'k), k\in\mathbb{Z}\}


*Your turn:  12x+15y=51*


Analytical DSS
--------------
**Idea** Design a analytical definition instead of combinatorial ones

.. admonition:: Def.

    `S\subset\mathbb{Z}^2`:math: is a *analytical DSS* with parameters `(a,b,\mu,\omega)\in\mathbb{Z}`:math: with `gcd(a,b)=1`:math:,  if for all `(x,y)\in S`:math:, we have

    .. math::
         0 \leq ax -by + \mu < \omega


* `\omega`:math: acts as a thickness (arithmetical thickness, >1)
* `\frac{a}{b}`:math: is the DSS slope
* `\mu`:math: is the arithmetical intercept

* S is the union of solutions of `\omega-1`:math: diophantine equations:

   .. math::
      S = \bigcup_{k=1..\omega-1} \{(x,y)\in\mathbb{Z}^2\,|\, ax -by = k - \mu\}


Illustration
------------

  .. image:: ./_static/images/droite_cont.*
     :width: 81%

Illustration
------------

  .. image:: ./_static/images/droite_cont_1.*
     :width: 80%

Illustration
------------

  .. image:: ./_static/images/droite_cont_2.*
     :width: 80%

Illustration
------------

  .. image:: ./_static/images/droite_cont_3.*
     :width: 80%

Illustration
------------

  .. image:: ./_static/images/droite_cont_4.*
     :width: 84%



Connectivity
------------

.. admonition:: Thm.

     `D(a,b,\mu,\omega)`:math:

     * If `\omega < \max(|a|,|b|)`:math:, D is not a (k)-path
     * If `\omega = \max(|a|,|b|)`:math:, D is a (0)-arc
     * If `\omega = |a|+|b|`:math:, D is a (1)-arc
     * If `\max(|a|,|b|) < \omega < |a|+|b|`:math:, D is  (*)-connected
     * If `\omega > |a|+|b|`:math:, D is  *thick*

.. list-table::

  * - .. image:: _static/images/3_7_0_5.*
          :width: 100%

    - .. image:: _static/images/3_7_0_7.*
          :width: 100%

    - .. image:: _static/images/3_7_0_8.*
          :width: 100%

    - .. image:: _static/images/3_7_0_10.*
          :width: 100%

    - .. image:: _static/images/3_7_0_16.*
          :width: 100%

  * - D(3,7,0,5)

    - D(3,7,0,7)

    - D(3,7,0,8)

    - D(3,7,0,10)

    - D(3,7,0,16)


Links between DSS and classical digitization scheme
---------------------------------------------------

Given an Euclidean straight line `d:\, ax - by + \mu=0`:math: with `\{a,b,\mu\}\in\mathbb{Z}`:math:
Without loss of generality, we suppose `b=|b|=\max(|a|,|b|)`:math:

* `D(a,b,\mu,b)`:math: corresponds to a kind of **OBQ** of d


   .. math::
     \{(x,y)\,|\, y= \left \lfloor \frac{-ax-\mu}{b}  \right  \rfloor     \}

* `D(a,b,\mu+b-1,b)`:math: corresponds to a kind of **BBQ** of d


   .. math::
     \{(x,y)\,|\, y=\left \lceil \frac{-ax-\mu}{b}    \right\rceil     \}

* `D(a,b,\mu+[\frac{b}{2}],b)`:math: corresponds to the **GIQ** quantization of d

   .. math::
     \{(x,y)\,|\, y=\left [ \frac{-ax-\mu}{b} \right ]   \}



* `D(a,b,\mu+[\frac{a+b}{2}],a+b+1)`:math: corresponds to the **supercover digitization** of d (analytical digitization with squares)


Periodicity
-----------


.. admonition:: Thm.

     Given  `D(a,b,\mu,\omega)`:math:, D is invariant by translation with vector `k.(b,a)^T`:math: (`k\in\mathbb{Z}`:math:)


*<proof>*


**Corollary**



.. admonition:: Coro.

 Any sequence of `b`:math: pixels defines a DSS *pattern*, the pattern is minimal iff `gcd(a,b)=1`:math:


Similar results than the one obtained by straight segment digitization but more generic


Toward stronger arithmetical results on DSS
===========================================


Farey Series
------------

.. admonition:: Def.

   The Farey Series `\mathcal{F}_m`:math: of order m is the ordered sequence of irreducible fractions with denominator less or equal to m


e.g.:
  .. math::
    \mathcal{F}_5=\left       \{\frac{0}{1},\frac{1}{5},\frac{1}{4},\frac{1}{3},\frac{2}{5},\frac{1}{2},\frac{3}{5},\frac{2}{3},\frac{3}{4},\frac{4}{5},\frac{1}{1}\right \}


**Properties**

* if `\frac{h}{k}`:math: et `\frac{h'}{k'}`:math: are two successive fractions in `\mathcal{F}_m`:math: (with `\frac{h}{k}<\frac{h'}{k'}`:math:), then  `kh'-hk'=1`:math:
* if `\frac{h}{k}`:math:, `\frac{h''}{k''}`:math: and `\frac{h'}{k'}`:math: are three successive fractions in `\mathcal{F}_m`:math: (with `\frac{h}{k}<\frac{h''}{k''}<\frac{h'}{k'}`:math:), then `\frac{h''}{k''}=\frac{h+h'}{k+k'}`:math: (*median fraction*)

* `\mathcal{F}_{m+1}`:math:  is given from  `\mathcal{F}_m`:math:  inserting median of successive fractions with denominator  `\leq m+1`:math:

 .. math::
   \mathcal{F}_6=\left    \{\frac{0}{1},{\bf         \frac{1}{6}},\frac{1}{5},\frac{1}{4},\frac{1}{3},\frac{2}{5},\frac{1}{2},\frac{3}{5},\frac{2}{3},\frac{3}{4},\frac{4}{5},{\bf \frac{5}{6}},\frac{1}{1}\right \}

Stern-Brocot Tree
-----------------

.. image:: _static/images/Sternbrocot.*
    :width: 100%
    :align: center


*Binary search tree on* `\mathcal{F}_m`:math: *fractions*


Composition of DSS pattern
--------------------------

**Given**

* `D_1`:math: with slope `\frac{u_1}{v_1}`:math: and Freeman code of one of its pattern `C_1`:math:
* `D_2`:math: with slope `\frac{u_2}{v_2}`:math: and Freeman code of
  one of its pattern `C_2`:math:
* `\frac{u_1}{v_1}< \frac{u_2}{v_2}`:math:
* and `u_2v_1 - u_1v_2 = 1`:math: (unimodularity)


**Then**

`\Rightarrow`:math: `C_1C_2`:math: is the Freeman code of one period of the DSS with slope `\frac{u_1+u_2}{v_1+v_2}`:math:


Illustration
------------

.. image:: _static/images/sternfreeman.*
    :width: 100%

All patterns: applications to DSS pattern intersection
------------------------------------------------------



   .. image:: _static/images/stern/stern-brocot_motifs-res.*
      :width: 82%

All patterns: applications to DSS pattern intersection
------------------------------------------------------

   .. image:: _static/images/stern/stern-brocot_chemin1-res.*
      :width: 80%


All patterns: applications to DSS pattern intersection
------------------------------------------------------


   .. image:: _static/images/stern/stern-brocot_chemin2-res.*
      :width: 80%

All patterns: applications to DSS pattern intersection
------------------------------------------------------



   .. image:: _static/images/stern/stern-brocot_chemin3-res.*
      :width: 80%


All patterns: applications to DSS pattern intersection
------------------------------------------------------


   .. image:: _static/images/stern/stern-brocot_chemin4-res.*
      :width: 80%

All patterns: applications to DSS pattern intersection
------------------------------------------------------


   .. image:: _static/images/stern/stern-brocot_chemin5-res.*
      :width: 80%

All patterns: applications to DSS pattern intersection
------------------------------------------------------


   .. image:: _static/images/stern/stern-brocot_chemin6-res.*
      :width: 80%

All patterns: applications to DSS pattern intersection
------------------------------------------------------


   .. image:: _static/images/stern/stern-brocot_chemin_dte2-res.*
      :width: 86%

All patterns: applications to DSS pattern intersection
------------------------------------------------------



   .. image:: _static/images/stern/stern-brocot_2dtes_bis-res.*
      :width: 86%


All patterns: applications to DSS pattern intersection
------------------------------------------------------


   .. image:: _static/images/pattern2.*
      :width: 90%


Object Recognition
==================


Recognition Algorithm
---------------------


**Idea**

Given a digital set `S`:math:, and a geometrical primitive (DSS,
Digital circle, digital plane, ...), decide if `S`:math: is a subset
of such primitive

* *Detection* Yes/No answer
* *Recognition* a valid parametrization of the primitive, the complete set of primitives containing `S`:math: **-> preimage**


   .. image:: _static/images/pixels-res.*
       :width: 40%


**Useful to**

* Perform contour polygonalization/decomposition into primitives
* Define multigrid convergent differential estimators


Geometrical Recognition (1)
---------------------------

**Idea**

Revert the digitization process and solve a *dual* problem

**DSS: Linear dual space**

.. list-table::


  * -  .. image:: _static/images/esp_param1-res.*
           :width: 120%
           :align: center

    -  .. image:: _static/images/esp_param2-res.*
           :width: 55%
           :align: center

    -  .. image:: _static/images/esp_param3-res.*
           :width: 60%
           :align: center


Geometrical Recognition (2)
---------------------------

Let us consider the following OBQ digitization scheme of `l: ax - by + \mu=0`:math:


   .. image:: _static/images/droite_OBQ-res.*
       :width: 50%


Each pixel `(x_0,y_0)`:math:  contributes to two linear constraints:

   .. math::
     0  \leq \alpha x_0 - y_0 + \beta < 1

.. list-table::

  * - .. image:: _static/images/pixel_OBQ-res.*
         :width: 40%
         :align: center

    - .. image:: _static/images/dual_OBQ-res.*
         :width: 40%
         :align: center


Geometrical Recognition (3)
---------------------------

**Algorithm principle**

Given a set S of pixels

* Start with a domain in the dual space `\bar{S}`:math: (i.e. we consider DSS in the first octant)
* For each pixel, compute the intersection between `\bar{S}`:math: and the two associated constraints

`\Rightarrow`:math: if  `\bar{S}`:math: is empty, **S is not a DSS (for OBQ scheme)**


`\bar{S}`:math: is called the *preimage* of S



Example
-------


.. list-table::

  * - .. image:: _static/images/dual_pixels1-res.*
         :width: 100%
         :align: center

    - .. image:: _static/images/dual_naive1-res.*
          :width: 100%
          :align: center


`a=(2,2)`:math: , `D_a: 2\alpha - 2+\beta=0`:math: and `D'_a: 2\alpha - 2+\beta=1`:math:


Example
-------


.. list-table::

  * - .. image:: _static/images/dual_pixels2-res.*
         :width: 100%
         :align: center

    - .. image:: _static/images/dual_naive2-res.*
          :width: 100%
          :align: center


`b=(4,3)`:math: , `D_b: 4\alpha - 3+\beta=0`:math: and `D'_b: 4\alpha - 3+\beta=1`:math:


Example
-------


.. list-table::

  * - .. image:: _static/images/dual_pixels3-res.*
         :width: 100%
         :align: center

    - .. image:: _static/images/dual_naive3-res.*
          :width: 100%
          :align: center


`c=(8,4)`:math: , `D_c: 8\alpha - 4+\beta=0`:math: and `D'_c: 8\alpha - 4+\beta=1`:math:


Example
-------


.. list-table::

  * - .. image:: _static/images/dual_pixels4bis-res.*
         :width: 100%
         :align: center

    - .. image:: _static/images/dual_naive4bis-res.*
          :width: 100%
          :align: center


`d=(9,5)`:math:, `D_d: 9\alpha - 5+\beta=0`:math: and `D'_d: 9\alpha - 5+\beta=1`:math:

Example
-------


.. list-table::

  * - .. image:: _static/images/dual_pixels_final-res.*
         :width: 100%
         :align: center

    - .. image:: _static/images/dual_naive_final-res.*
          :width: 100%
          :align: center

`p=\left(\frac{1}{3},2\right)`:math: in the dual space leads to `l: \frac{1}{3}x -y +2 = 0`:math:


Computational cost
------------------

**Preimage = Classical linear programming problem**

* We only have linear constraints
* `\bar{S}`:math: is convex
* on-line recognition algorithm in `O(n\log(n))`:math: to maintain `\bar{S}`:math: (`O(\log(n))`:math: per constraint)
* Detection in `O(n)`:math:


**If** `S`:math: **is a (0)-path**


.. admonition:: Thm.

    `\bar{S}`:math: has at most 4 vertices in the dual space

  .. image:: _static/images/structure_ilroy.*
      :width: 60%
      :align: center


`\Rightarrow`:math: *On-line DSS recognition in* `O(n)`:math: *(O(1) per constraint)*



Algorithm
---------

  .. image:: _static/images/preimage-algo.*
      :width: 100%


Rationale of the preimage structure
-----------------------------------

**Farey Fan**

The Farey Fan of order `n`:math: is a decomposition of the space into cells where each cell corresponds to a DSS preimage of length `n+1`:math:


.. list-table::

 *   -  .. image:: _static/images/farey_fan_2.*
          :width: 100%

     -  .. image:: _static/images/farey_fan_3.*
          :width: 100%

     -  .. image:: _static/images/farey_fan_6.*
          :width: 100%


 * - Order 2

   - Order 3

   - Order 6

DSS and Farey Fan Cell
----------------------


  .. image:: _static/images/fareyfan5.*
          :width: 100%


Arithmetical Recognition
------------------------


**Idea**

Use the analytical representation of DSS:

* `D(a,b,\mu)`:math: a DSS in the first octant
*  the *reminder* of a pixel `(x,y)`:math: is the quantity

   .. math:: r = ax- by

* the k-th *net* is defined by the solutions of

   .. math:: ax -by =k

* the DSS is the union of nets with `k\in\{\mu,\ldots,\mu + b - 1\}`:math:



**Definitions (again)**

.. admonition:: Defs.

    *  `(x,y)`:math: is  *exterior* to D if its reminder is lesser than `\mu-1`:math: or greater than `\mu+b`:math:
    *  `(x,y)`:math: is *weakly exterior* to D if its reminder is equal to `\mu-1`:math: or  `\mu+b`:math:
    *  The net with order `\mu`:math: is the *upper leaning* net
    *  The net with order `\mu+b-1`:math: is the *lower leaning* net


Illustration
------------


  .. image:: _static/images/reveilles_appui.*
      :width: 100%


Main Recognition Theorem
------------------------

Let U (resp. U') be the upper leaning point with minimal abscissa (maximal abscissa) and L (resp. L') be the lower leaning point with minimal abscissa (maximal abscissa)

Given a DSS digital set S w and a point M (with reminder r), we have to decide if `S\cup\{M\}`:math: is still a DSS

.. admonition:: Thm.

  * if `\mu \leq r < \mu+b`:math: then `S\cup\{M\}`:math: is a DSS with parameter `D(a,b,\mu)`:math:
  * if M is *exterior*,  `S\cup\{M\}`:math:  cannot be a DSS
  * if M is *weakly exterior* with `r=\mu+1`:math:, `S\cup\{M\}`:math: is a DSS where the slope is given by `\vec{UM}`:math:
  * if M is *weakly exterior* with `r=\mu+b`:math:, `S\cup\{M\}`:math: is a DSS where the slope is given by `\vec{LM}`:math:

  At each step, we maintain/update U,U',L,L' and DSS parameters a,b, `\mu`:math:

Theorem cases
-------------

 .. image:: _static/images/algo_debled.*
     :width: 100%

Algorithm
---------

  .. image:: _static/images/debled-algo.*
      :width: 80%


Analysis
--------

**Computational cost**

* `O(n)`:math: algorithm with `O(1)`:math: per pixel
* possible to design dynamic bidirectionnal algorithm (we can add/remove points on both sides) with same complexity


**Key point of the proof: unimodular vectors**

Given two vectors `\vec{u},\vec{v}\in\mathbb{Z}^2`:math:, `\vec{u}`:math: and `\vec{v}`:math: are unimodular iff `det(u,v) \pm 1`:math:

E.g. `\vec{UU'}`:math: and `\vec{UM}`:math: are unimodular if `M`:math: is *weakly superior*

(if vectors define fractions, fractions are neighbors in a given Farey series)


*Unimodular means that there is no integer point in the parallelogram* (`\vec{u},\vec{v}`:math:)

 .. image:: _static/images/unimodular.*
    :width: 60%


Example
-------

 .. image:: _static/images/algo_debled_run.*
     :width: 100%


Digital Plane
-------------

**Similar approaches**

* Definition as the result of a digitization process
* Analytical definition: `P(a,b,c,\mu,\omega): \mu \leq ax + by + cz \leq \mu + \omega`:math: with similar topological results according to `\omega`:math: , with similar arithmetical structure (leaning points, unimodular vectors, ...)

.. list-table::

  * - .. image:: _static/images/plan_fin.*
       :width: 100%

    - .. image:: _static/images/plan_naif.*
       :width: 100%

    - .. image:: _static/images/plan_stand.*
       :width: 100%


  * - P(6,13,27,0,15)

    - P(6,13,27,0,27)

    - P(6,13,27,0,46)



General Approach for Recognition Algorithm Design
-------------------------------------------------

**Digitization -> Constraints**

Given the primitive (plan, circle, ...), digitization usually implies inequality system we have to solve

Usually:

* Coefficients in the inequalities are usually integers
* Easier if we can *linearize* the system (even in higher dimensions, e.g. 3 for circles)


**Regularity/arithmetic in analytical representation**

* Leads to more efficient algorithms
* Difficult for high order primitives or in higher dimension

**Design the recognition as a separation problem with tools from Computational Geometry**

* E.g. disc recognition as a separability problem with Euclidean arc between interior/exterior point sets.


*In practice: a kind of mix between all these approaches...*




Contour Polygonalization
========================



Contour Decomposition into maximal DSS
--------------------------------------

**Idea**

Starting from a  contour point (and given a direction), decompose the contour into maximal DSS adding pixels one by one

.. list-table::

 * - .. image:: _static/images/cercle_segm.*
          :width: 100%

   - .. image:: _static/images/carre_segm.*
          :width: 100%

   - .. image:: _static/images/sinc_segm.*
          :width: 100%


`\Rightarrow`:math: **O(n) algorithm**


`\Rightarrow`:math: **Changing the starting point, decompositions differs by one (N, N+1)**



In 3D...
--------

**Similar approach but**

1) No trivial order
2) Heuristic to scatter seeds for the incremental recognition
3) Parallel or sequential process

**Usually**

* Geodesic one to generate as anisotropic as possible DPS patches
* Using curvature information in parallel mode



.. list-table::

 * - .. image:: _static/images/al.*
         :width: 70%

   - .. image:: _static/images/dodgePlans.*
         :width: 100%


Back in 2D: Polygonalization problem
------------------------------------

**Principle**

Convert a digital contour into a polygon such that *its digitization is the input digital set*

**First approach: use DSS decomposition**

Indeed, DSS segments are "reversible" ... but not the vertices..


.. list-table::

 * - .. image:: _static/images/contre_ex_methode_naive_2D.*
          :width: 100%

   - .. image:: _static/images/revproblem.*
          :width: 65%



`\Rightarrow`:math:  We need to constraint the preimages to ensure that successive DSSs have euclidean representative segment with "reversible" intersection vertex


Example of a solution in 2D
---------------------------


  .. image:: ./_static/images/pixels_courbe0-res.*
     :width: 70%

Example of a solution in 2D
---------------------------

  .. image:: ./_static/images/pixels_courbe0bis-res.*
     :width: 70%

Example of a solution in 2D
---------------------------

  .. image:: ./_static/images/pixels_courbe-res.*
     :width: 70%

Example of a solution in 2D
---------------------------

  .. image:: ./_static/images/pixels_courbe3-res.*
     :width: 70%


Example of a solution in 2D
---------------------------

  .. image:: ./_static/images/pixels_courbe4-res.*
     :width: 70%


Reversible reconstruction in dimension 3
----------------------------------------

More difficult because of topological issues.

**Idea**: start from a topologically valid reversible triangulation (*Marching Cubes*), merge triangles using digital plane decomposition information and constraints on preimage


 .. image:: _static/images/resultats.png
     :width: 70%



(Marching Cubes)
----------------


 .. image:: _static/images/MC.*
     :width: 100%

 .. image:: _static/images/spheremc.*
     :width: 30%


* Reversible polyhedron
* Topologically correct (combinatorial 2-manifold)
* ... but many facets

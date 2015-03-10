Image Processing, Digital Geometry and Computational Geometry Course
====================================================================

This material corresponds to a course on elementary image processing, digital geometry and computational geometry. In French, it corresponds to the lecture "Images Numériques et Géométrie Discrète" at the ENS-Lyon (Ecole Normale Supérieure de Lyon) and Univesité Claude Bernard Lyon 1.

First slides are in French but most of them are in English. The content is "work in progress" and is updated continously. As a consequence, it may contain errors. If you found some, please contact the author or create a <a href="https://github.com/dcoeurjo/lectureDG/issues/new">github issue</a>.

Content
-------

This repository contains all the material to build the lecture slides,
the course notes and practical work exercises.  The lecture content is
given as collection of ReST (restructured text) files.  To build the
slides, you would need:

  - Sphinx (Python Documentation Generator, http://sphinx-doc.org) to generate PDF, latex, HTML, ... outputs
  - hieroglyph (https://github.com/nyergler/hieroglyph) to generate the HTML5 slide output.

Once installed, the build is rather simple:

    make html
    make latexpdf

or

    make slides


Then, the output is given in the *build* folder.

Examples:
  - HTML pages: https://liris.cnrs.fr/david.coeurjolly/cours/ENS2015/html/
  - HTML5 slides: https://liris.cnrs.fr/david.coeurjolly/cours/ENS2015/html/slides/
  - PDF single document: https://liris.cnrs.fr/david.coeurjolly/cours/ENS2015/latex/Images.pdf


Author
------

David Coeurjolly (http://liris.cnrs.fr/david.coeurjolly)
david.coeurjolly@liris.cnrs.fr

Copyright
---------

The overall material is distributed using the BY-NC-ND Creative Commons Licence <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/2.0/fr/deed.en"><img alt="Creative Commons License" style="border-width:0" src="http://i.creativecommons.org/l/by-nc-nd/2.0/fr/88x31.png" /></a><br /> <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/2.0/fr/deed.en">Creative Commons Attribution-NonCommercial-NoDerivs 2.0 France License</a>.

If you want to use distribute derivative of this work for your own purposes, contact the author.

Illustrations come from many sources (previous lectures, personnal tech reports, wikipedia...). I've tried to detail credits for them but if you see issues, please send me a mail.
Some of them have been provided by colleagues and I'd like to thank them: Jacques-Olivier Lachaud, Tristan Roussillon, Isabelle Sivignon, Olivier Devillers, Nicolas Normand and Guillaume Iooss.




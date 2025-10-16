*KEYWORD
*TITLE
Simple Sphere Impact on Plate - LSDYNA Example

*DATABASE_FORMAT
         0

$--- 1. CONTROL CARDS ---
*CONTROL_TERMINATION
$   endtim    endcyc     dtmin    endeng    endmas
      10.0         0       0.0       0.01.000000E8

*CONTROL_TIMESTEP
$    dtinit    tssfac      isdo    tslimt     dt2ms      lctm     erode     ms1st
       0.0      0.9         0       0.0       0.0         0         0         0

*CONTROL_SHELL
$   wrpang     itrist     irnxx    istupd    theory       bwc     miter      proj
      20.0         2        -1         1         2         2         1         0

*CONTROL_CONTACT
$   slsfac    rwpnal    islchk    shlthk    penopt    thkchg     orien    enmass
       0.1       1.0         2         2         1         0         1         0

*CONTROL_ENERGY
$    hgen      rwen    slnten     rylen
         2         2         2         2

*CONTROL_OUTPUT
$   npopt    neecho    nrefup    iaccop     opifs    ipnint    ikedit    iflush
         1         3         0         0       0.0         0         0       500

$--- 2. DATABASE OUTPUT ---
*DATABASE_BINARY_D3PLOT
$       dt      lcdt      beam     npltc    psetid
       1.0         0         0         0         0

*DATABASE_BINARY_D3THDT
$       dt      lcdt
       0.1         0

*DATABASE_EXTENT_BINARY
$   neiph     neips    maxint    strflg    sigflg    epsflg    rltflg    engflg
        10        10         3         1         1         1         1         1

*DATABASE_HISTORY_NODE
$      id1       id2       id3       id4       id5       id6       id7       id8
       101       201         0         0         0         0         0         0

*DATABASE_HISTORY_SOLID
$      id1       id2       id3       id4       id5       id6       id7       id8
         1         2         0         0         0         0         0         0

$--- 3. MATERIAL DEFINITIONS ---
*MAT_ELASTIC
$      mid        ro         e        pr        da        db         k
         1 7.850E-9   210000.0       0.3       0.0       0.0       0.0

*MAT_PLASTIC_KINEMATIC
$      mid        ro         e        pr      sigy      etan      beta
         2 7.850E-9   210000.0       0.3     400.0    2000.0       1.0

*MAT_RIGID
$      mid        ro         e        pr         n    couple         m        alias
         3 7.850E-9   210000.0       0.3       0.0       0.0       0.0        

$--- 4. SECTION DEFINITIONS ---
*SECTION_SOLID
$     secid    elform       aet
         1         1         0

*SECTION_SHELL
$     secid    elform      shrf       nip     propt   qr/irid     icomp     setyp
         2         2       1.0         2       1.0         0         0         1

$--- 5. PART DEFINITIONS ---
*PART
$      pid     secid       mid     eosid      hgid      grav    adpopt      tmid
Sphere Part
         1         1         2         0         0         0         0         0

*PART
$      pid     secid       mid     eosid      hgid      grav    adpopt      tmid
Plate Part
         2         2         1         0         0         0         0         0

*PART
$      pid     secid       mid     eosid      hgid      grav    adpopt      tmid
Fixed Boundary
         3         2         3         0         0         0         0         0

$--- 6. NODE DEFINITIONS ---
*NODE
$     nid               x               y               z      tc      rc
       101         0.0000         0.0000        50.0000       0       0
       102         5.0000         0.0000        50.0000       0       0
       103         0.0000         5.0000        50.0000       0       0
       104        -5.0000         0.0000        50.0000       0       0
       105         0.0000        -5.0000        50.0000       0       0
       201         0.0000         0.0000         0.0000       0       0
       202        20.0000         0.0000         0.0000       0       0
       203         0.0000        20.0000         0.0000       0       0
       204       -20.0000         0.0000         0.0000       0       0
       205         0.0000       -20.0000         0.0000       0       0
       301        50.0000        50.0000         0.0000       0       0
       302        50.0000       -50.0000         0.0000       0       0
       303       -50.0000        50.0000         0.0000       0       0
       304       -50.0000       -50.0000         0.0000       0       0

$--- 7. ELEMENT DEFINITIONS ---
*ELEMENT_SOLID
$     eid     pid      n1      n2      n3      n4      n5      n6      n7      n8
         1       1     101     102     103     104     105     102     103     104

*ELEMENT_SHELL
$     eid     pid      n1      n2      n3      n4
         1       2     201     202     203     201
         2       2     201     203     204     201
         3       2     201     204     205     201
         4       2     201     205     202     201

*ELEMENT_SHELL
$     eid     pid      n1      n2      n3      n4
         5       3     301     302     304     303

$--- 8. CONTACT DEFINITIONS ---
*CONTACT_AUTOMATIC_SURFACE_TO_SURFACE
$     cid      ssid      msid     sstyp     mstyp    sboxid    mboxid       spr       mpr
         1         1         2         3         3         0         0       0.0       0.0
$       fs        fd        dc        vc       vdc    penchk        bt        dt
       0.2       0.1       0.0       0.0       0.0         0       0.01.000000E20
$      sfs       sfm       sst       mst      sfst      sfmt       fsf       vsf
       1.0       1.0       0.0       0.0       0.0       0.0       1.0       1.0

$--- 9. BOUNDARY CONDITIONS ---
*BOUNDARY_SPC_SET
$      nid       cid      dofx      dofy      dofz     dofrx     dofry     dofrz
         1         0         1         1         1         1         1         1
         2         0         0         0         0         1         1         1
         3         0         0         0         0         1         1         1
         4         0         0         0         0         1         1         1
         5         0         0         0         0         1         1         1

*BOUNDARY_SPC_NODE
$      nid       cid      dofx      dofy      dofz     dofrx     dofry     dofrz
       301         0         1         1         1         1         1         1
       302         0         1         1         1         1         1         1
       303         0         1         1         1         1         1         1
       304         0         1         1         1         1         1         1

$--- 10. INITIAL CONDITIONS ---
*INITIAL_VELOCITY
$     nsid       dof       vid      vadh
         1         3  -1000.0         0

*INITIAL_VELOCITY_NODE
$      nid       dof      vold      vnew
       101         3  -1000.0  -1000.0
       102         3  -1000.0  -1000.0
       103         3  -1000.0  -1000.0
       104         3  -1000.0  -1000.0
       105         3  -1000.0  -1000.0

$--- 11. SET DEFINITIONS ---
*SET_NODE_LIST
$      sid       da1       da2       da3       da4
         1       0.0       0.0       0.0       0.0
$     nid1      nid2      nid3      nid4      nid5      nid6      nid7      nid8
       101       102       103       104       105         0         0         0

*SET_PART_LIST
$      sid       da1       da2       da3       da4
         1       0.0       0.0       0.0       0.0
$     pid1      pid2      pid3      pid4      pid5      pid6      pid7      pid8
         1         0         0         0         0         0         0         0

$--- 12. HOURGLASS CONTROL ---
*HOURGLASS
$      hid        hg        ihq        qm       ibq        q1        q2      qb/qw
         1         1       0.03       0.0       0.0       0.0       0.0       0.0

$--- 13. LOAD DEFINITIONS ---
*LOAD_BODY_Z
$      lcid        sf    lciddr        xc        yc        zc       cid
         1      9806.0         0       0.0       0.0       0.0         0

*DEFINE_CURVE
$     lcid      sidr      scla      sclo      offa      offo      dtyp      lcint
         1         0       1.0       1.0       0.0       0.0         0         0
$               a1                  o1
                0.0                 1.0
               10.0                 1.0

$--- 14. EOS (EQUATION OF STATE) ---
*EOS_LINEAR_POLYNOMIAL
$    eosid        c0        c1        c2        c3        c4        c5        c6
         1       0.0       0.0       0.0       0.0       0.0       0.0       0.0
$       e0        v0
       0.0       0.0

$--- 15. CONSTRAINED NODAL RIGID BODY ---
*CONSTRAINED_NODAL_RIGID_BODY
$     pidn      pids      iflag     iform     dtout
         3         0         0         0       0.0

$--- 16. DATABASE OPTIONS ---
*DATABASE_NODFOR
$       dt      lcdt
       0.1         0

*DATABASE_RCFORC
$       dt      lcdt
       0.1         0

*DATABASE_GLSTAT
$       dt      lcdt
       0.1         0

*DATABASE_MATSUM
$       dt      lcdt
       0.1         0

*DATABASE_RBDOUT
$       dt      lcdt
       0.1         0

*DATABASE_SLEOUT
$       dt      lcdt
       0.1         0

*DATABASE_BNDOUT
$       dt      lcdt
       0.1         0

*END
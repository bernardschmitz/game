import Blender
import math

out = open("z:\\cross\\game\\graphics\\object.c", "w")

print "opened file..."

#print Blender.Object.Get()


mh = {}
mi = 0
for m in Blender.Material.Get():
  #print mi, mat
  print "exporting material %s..." % m.name
  mh[m.name] = mi
  out.write( "// %s material\n" % m.name)
  out.write( "static GLfloat mat_%d_diffuse[] = { %f, %f, %f, %f };\n" % (mi, m.R, m.G, m.B, m.alpha) )
  out.write( "static GLfloat mat_%d_ambient[] = { %f, %f, %f, 1.0 };\n" % (mi, m.R*m.amb, m.G*m.amb, m.B*m.amb) )
  out.write( "static GLfloat mat_%d_specular[] = { %f, %f, %f, 1.0 };\n" % (mi, m.specR*m.spec, m.specG*m.spec, m.specB*m.spec) )
  out.write( "static GLfloat mat_%d_emission[] = { %f, %f, %f, 1.0 };\n" % (mi, m.R*m.emit, m.G*m.emit, m.B*m.emit) )
  out.write( "static GLfloat mat_%d_shine = %f;\n" % (mi, m.hard*128.0/255.0) )
  mi = mi + 1

oi = 0
for obj in Blender.Object.Get():

  ot = obj.getType()

  if ot == "Empty":
    print obj.name, obj.loc

  if ot == "Mesh":

    #print obj.parent

    print "exporting mesh %s..." % obj.data.name
    out.write("\n// %s\n" % obj.data.name)

    out.write( "glPushMatrix();\n" )
    out.write( "glTranslatef(%f, %f, %f);\n" % (obj.loc[0], obj.loc[1], obj.loc[2]))
    out.write( "glScalef(%f, %f, %f);\n" % (obj.size[0], obj.size[1], obj.size[2]))
    out.write( "glRotatef(%f*180.0/M_PI, 1.0, 0.0, 0.0);\n" % (obj.rot[0]))
    out.write( "glRotatef(%f*180.0/M_PI, 0.0, 1.0, 0.0);\n" % (obj.rot[1]))
    out.write( "glRotatef(%f*180.0/M_PI, 0.0, 0.0, 1.0);\n" % (obj.rot[2]))

    nmesh = Blender.NMesh.GetRaw(obj.data.name)

    # get materials
    mats = nmesh.materials
    #print mats[0].name, mh[mats[0].name]

    for sides in (2, 3, 4):
      if sides == 2:
        type = "glBegin(GL_LINES);\n"
      else:
        if sides == 3:
          type = "glBegin(GL_TRIANGLES);\n"
        else:
          type = "glBegin(GL_QUADS);\n"
    
      old_mat = -1

      for f in nmesh.faces:

        if len(f.v) == sides:  
          # if not smooth and not edge then calculate face normal  
          if not f.smooth and sides != 2:
            a0 = f.v[2][0] - f.v[1][0]
            a1 = f.v[2][1] - f.v[1][1]
            a2 = f.v[2][2] - f.v[1][2]
      
            b0 = f.v[0][0] - f.v[1][0]
            b1 = f.v[0][1] - f.v[1][1]
            b2 = f.v[0][2] - f.v[1][2]
      
            nx = a1*b2 - a2*b1
            ny = a2*b0 - a0*b2
            nz = a0*b1 - a1*b0
      
            mag = nx*nx+ny*ny+nz*nz
      
            if mag > 0.0:
              mag = math.sqrt(mag)
              nx = nx / mag
              ny = ny / mag
              nz = nz / mag

            # output primitive type if not done so
            if type != "":
              out.write(type)
              type = ""

            out.write("  glNormal3f(%f, %f, %f);\n" % (nx, ny, nz))
      
          # output each vertex and associated info
          if f.mat != old_mat:
             old_mat = f.mat
             mm = mh[mats[f.mat].name]
             out.write(" glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_%d_diffuse);\n" % (mm))
             out.write(" glMaterialfv(GL_FRONT, GL_AMBIENT, mat_%d_ambient);\n" % (mm))
             out.write(" glMaterialfv(GL_FRONT, GL_SPECULAR, mat_%d_specular);\n" % (mm))
             out.write(" glMaterialf(GL_FRONT, GL_SHININESS, mat_%d_shine);\n" % (mm))
             out.write(" glMaterialfv(GL_FRONT, GL_EMISSION, mat_%d_emission);\n" % (mm))
 
          i = 0
          for v in f.v:
            # output primitive type if not done so
            if type != "":
              out.write(type)
              type = ""

            if nmesh.hasVertexColours():
              out.write( "  glColor4d(%d, %d, %d, %d);\n" % (f.col[i].r, f.col[i].g, f.col[i].b, f.col[i].a))

            if nmesh.hasFaceUV():
              out.write( "  glTexCoord2f(%f, %f);\n" % (f.uv[i][0], f.uv[i][1]))

            if f.smooth:
              out.write( "  glNormal3f(%f, %f, %f);\n" % (v.no[0], v.no[1], v.no[2]))

            out.write( "  glVertex3f(%f, %f, %f);\n" % (v.co[0], v.co[1], v.co[2]))
            i = i + 1
      
      if type == "":
        out.write( "glEnd();\n\n")

    out.write( "glPopMatrix();\n" )
  oi = oi + 1
out.close()
print "done."      
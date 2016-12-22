//importo le librerie kinect e blobdetection
import org.openkinect.freenect.*;
import org.openkinect.processing.*;
import org.openkinect.tests.*;
import blobDetection.*;

//inizializzo kinect e blobdetection
Kinect kinect;
BlobDetection theBlobDetection;

//creo l'immagine sulla quale stampo i pixel con i dati di kinect
PImage img;
//dichiaro due variabili che dopo userò per trovare il centroide del blob
float blobCenterX;
float blobCenterY;
//due variabili per settare il treshold di grandezza per i blob
float larghezzaMin;
float altezzaMin;

/*setto come distanza massima l'altezza sopra cui vengono iniziati a visualizzare i punti, 
 praticamente l'altezza minima che debba avere una persona affinchè funzioni tutto*/
int distMax = 900;  
/*setto come distanza minima un numero che mi assicura di poter eliminare l'intorno della visione che non
 ci interessa tipo le cose che potrebbero essere affianco kinect per esempio le robe per fissarlo al soffitto*/
int distMin = 300;



void setup() {
  //inizializzo ancora kinect
  size(640, 480);
  kinect = new Kinect(this);
  kinect.initDepth();
  img = createImage(kinect.width, kinect.height, RGB);

  //inizializzo ancora la blobdetection, passando alla libreria l'immagine di kinect
  theBlobDetection = new BlobDetection(img.width, img.height);
  theBlobDetection.setPosDiscrimination(true);
  //treshold di luminosità per i pixel affinchè i blob vengano creati
  theBlobDetection.setThreshold(0.2f);
}

void draw() {
  //salvo le informazioni di profondità di kinect in un array
  img.loadPixels();
  int[] depth = kinect.getRawDepth();

  //iterizzo tutti i pixel in modo da disegnare solo le teste di chi cammina

  for (int x = 0; x < kinect.width; x++) {
    for (int y = 0; y < kinect.height; y++) {
      int offset = x + y * kinect.width;
      int d = depth[offset];
      if ( d > distMin && d < distMax) {
        img.pixels[offset] = color(255, 0, 0);
      } else {
        img.pixels[offset] = color(0, 0, 0);
      }
    }
  }

  img.updatePixels();
  image(img, 0, 0);

  //blurro l'immagine e la passo al blobdetector che disegna i blob
  fastblur(img, 2);
  theBlobDetection.computeBlobs(img.pixels);
  drawBlobsAndEdges(true, true);

  /* =============== 
     ===============
 INIZIO DEFINIZIONE AREE DI ATTIVAZIONE DEI MARTELLI
     ===============
     ===============
  */

  // area di attivazione martello 1
  color Martello1 = color(0, 255, 150);
  fill(Martello1); //verde chiaro
  rect(100, 100, 50, 50, 15);
  // area di attivazione martello 2
  color Martello2 = color(0, 150, 255);
  fill(Martello2); //blu chiaro
  rect(100, 300, 50, 50, 15);

  //controllo se il centro del blob è dentro un area
  //rendo intere le variabili per il centroide e il treshold di grandezza
  int bX = int(blobCenterX);
  int bY = int(blobCenterY);

  int mA = int(altezzaMin);
  int mL = int(larghezzaMin);

  //calcolo il colore del centroide del blob
  color centroidColor = get(bX, bY);

  if ( mA > 15 && mA > 15) {  //solo se il blob è più grande di 15x15
    //se il colore del centroide e quello dell'area del martello coincidono vuol dire che qualcuno è nell'area
    if (centroidColor == Martello1) { //controllo area del martello1
      println("martello 1 attivo");
      //inserire arduino qua
    }

    if (centroidColor == Martello2) { //controllo area del martello2
      println("martello 2 attivo");
      //inserire arduino qua
    }
  }
}

/* ==============================
 =================================
 =================================
 CODICE LIBRERIA BLOB DETECTION
 =================================
 ================================= 
 ================================= */

void drawBlobsAndEdges(boolean drawBlobs, boolean drawEdges)
{
  noFill();
  Blob b;
  EdgeVertex eA, eB;
  for (int n=0; n<theBlobDetection.getBlobNb(); n++)
  {
    b=theBlobDetection.getBlob(n);
    if (b!=null)
    {
      // Edges
      if (drawEdges)
      {
        strokeWeight(3);
        stroke(0, 255, 0);
        for (int m=0; m<b.getEdgeNb(); m++)
        {
          eA = b.getEdgeVertexA(m);
          eB = b.getEdgeVertexB(m);
          if (eA !=null && eB !=null)
            line(
              eA.x*width, eA.y*height, 
              eB.x*width, eB.y*height
              );
        }
      }

      // Blobs
      if (drawBlobs)
      {
        strokeWeight(1);
        stroke(255, 0, 0);
        rect(
          b.xMin*width, b.yMin*height, 
          b.w*width, b.h*height
          );
        //calcolo il centro del blob
        blobCenterX = b.xMin*width + b.w*width / 2;
        blobCenterY = b.yMin*height + b.h*height / 2;
        //salvo larghezza e altezza del blob
        larghezzaMin = b.w*width;
        altezzaMin = b.h*height;
      }
    }
  }
}

void fastblur(PImage img, int radius)
{
  if (radius<1) {
    return;
  }
  int w=img.width;
  int h=img.height;
  int wm=w-1;
  int hm=h-1;
  int wh=w*h;
  int div=radius+radius+1;
  int r[]=new int[wh];
  int g[]=new int[wh];
  int b[]=new int[wh];
  int rsum, gsum, bsum, x, y, i, p, p1, p2, yp, yi, yw;
  int vmin[] = new int[max(w, h)];
  int vmax[] = new int[max(w, h)];
  int[] pix=img.pixels;
  int dv[]=new int[256*div];
  for (i=0; i<256*div; i++) {
    dv[i]=(i/div);
  }

  yw=yi=0;

  for (y=0; y<h; y++) {
    rsum=gsum=bsum=0;
    for (i=-radius; i<=radius; i++) {
      p=pix[yi+min(wm, max(i, 0))];
      rsum+=(p & 0xff0000)>>16;
      gsum+=(p & 0x00ff00)>>8;
      bsum+= p & 0x0000ff;
    }
    for (x=0; x<w; x++) {

      r[yi]=dv[rsum];
      g[yi]=dv[gsum];
      b[yi]=dv[bsum];

      if (y==0) {
        vmin[x]=min(x+radius+1, wm);
        vmax[x]=max(x-radius, 0);
      }
      p1=pix[yw+vmin[x]];
      p2=pix[yw+vmax[x]];

      rsum+=((p1 & 0xff0000)-(p2 & 0xff0000))>>16;
      gsum+=((p1 & 0x00ff00)-(p2 & 0x00ff00))>>8;
      bsum+= (p1 & 0x0000ff)-(p2 & 0x0000ff);
      yi++;
    }
    yw+=w;
  }

  for (x=0; x<w; x++) {
    rsum=gsum=bsum=0;
    yp=-radius*w;
    for (i=-radius; i<=radius; i++) {
      yi=max(0, yp)+x;
      rsum+=r[yi];
      gsum+=g[yi];
      bsum+=b[yi];
      yp+=w;
    }
    yi=x;
    for (y=0; y<h; y++) {
      pix[yi]=0xff000000 | (dv[rsum]<<16) | (dv[gsum]<<8) | dv[bsum];
      if (x==0) {
        vmin[y]=min(y+radius+1, hm)*w;
        vmax[y]=max(y-radius, 0)*w;
      }
      p1=x+vmin[y];
      p2=x+vmax[y];

      rsum+=r[p1]-r[p2];
      gsum+=g[p1]-g[p2];
      bsum+=b[p1]-b[p2];

      yi+=w;
    }
  }
}
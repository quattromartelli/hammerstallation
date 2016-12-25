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
//due variabili per settare il treshold di grandezza per i blob 
int larghezzaBlob;
int altezzaBlob;
//booleane per la comunicazione seriale con arduino. se una di queste è vera allora un martello deve essere attivato.
boolean posizione1;
boolean posizione2;

/*setto come distanza massima l'altezza sopra cui vengono iniziati a visualizzare i punti, 
 praticamente l'altezza minima che debba avere una persona affinchè funzioni tutto*/
int distMax = 900;  
/*setto come distanza minima un numero che mi assicura di poter eliminare l'intorno della visione che non
 ci interessa tipo le cose che potrebbero essere affianco kinect per esempio le robe per fissarlo al soffitto*/
int distMin = 300;

//setto i colori per le aree di attivazione che disegno alla fine del draw()
color Martello1 = color(0, 255, 150);
color Martello2 = color(0, 150, 255);

//variabile globale che serve per controllare la posizione del centroide del blob
int posx;
int posy;

//variabile globale colore che serve per controllare il colore del pixel cioè la posizione della persona
color currentColor;

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
   DISEGNO LE AREE DI ATTIVAZIONE DEI MARTELLI
   ===============
   ===============
   */

  // area di attivazione martello 1
  fill(Martello1); //verde chiaro
  rect(100, 100, 50, 50, 15);

  // area di attivazione martello 2
  fill(Martello2); //blu chiaro
  rect(100, 300, 50, 50, 15);


  /* =============== 
   ===============
   INIZIO CODICE PER ARDUINO
   ===============
   ===============
   */

  if (posizione1 == true) {
    println("martello 1 è attivo");
    //inserire qui riga che dice ad arduino di tirare su il martello
  }


  if (posizione2 == true) {
    println("martello 2 è attivo");
    //inserire qui riga che dice ad arduino di tirare su il martello
  }

  //prendo il colore alla posizione del centroide del blob (cioè della persona) e la comparo quando disegno i blob e i centroidi dei blob
  currentColor = get(posx, posy);
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
        noFill(); 
        rect(
          b.xMin*width, b.yMin*height, 
          b.w*width, b.h*height
          );

        //salvo larghezza e altezza del blob per creare un treshold di grandezza
        larghezzaBlob = int(b.w*width);
        altezzaBlob = int(b.h*height);

        //creo centroide con size treshold, altrimenti fa casini
        if (larghezzaBlob > 30 && altezzaBlob > 30) {  //il centroide verrà disegnato se il blob è più grande di 30x30
          BlobCenter bc;  //dichiaro un nuovo centroide
          bc = new BlobCenter( b.xMin*width+b.w*width/2, b.yMin*height+b.h*height/2); //chiamo il constructor
          bc.display(); //lo disegno
          posx = int(bc.unox); //interizzo le coordinate del centro
          posy = int(bc.duey);
          bc.check(currentColor);  //controllo la posizione nello spazio
        }
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

/* ==============================
 =================================
 =================================
 CLASSE BLOB CENTER
 =================================
 ================================= 
 ================================= */


class BlobCenter {
  float unox, duey;

  BlobCenter(float uno, float due) {
    unox = uno;
    duey = due;
  }
  void display() {
    fill(255);
    ellipse (unox, duey, 15, 15);
  }



  void check(color areacolor) {
    //se il colore del pixel della posizione del centroide corrisponde al colore dell'area di un martello, una booleana diventerà true
    if (areacolor == Martello1) { 
      posizione1 = true;
    } else {
      posizione1= false;
    }


    if (areacolor == Martello2) {
      posizione2 = true;
    } else {
      posizione2 = false;
    }
  }
}
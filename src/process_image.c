#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"



float get_pixel(image im, int x, int y, int c)
{  //padding
      if(x>=im.w) x = im.w-1;
      else if(x<0) x = 0;

      if(y>=im.h) y = im.h - 1;
      else if (y<0) y = 0;

      if(c>=im.c) c = im.c - 1;
      else if (c<0) c =0 ;

return im.data[x + (im.w)*y + (im.w)*(im.h)*c];
    
   
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if((x>im.w)||(x<0)||(y<0)||(y>im.h)){
        return;
    }
    else{
        im.data[x + (im.w)*y + (im.w)*(im.h)*c] = v;

    }
   
    
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
  //  memcpy(copy,im);
    
    for(int i=0; i<im.c; i++){
        for(int j=0; j<im.h; j++){
            for(int k=0; k<im.w; k++){
                copy.data[k + (copy.w)*j + (copy.w)*(copy.h)*i] = im.data[k + (im.w)*j + (im.w)*(im.h)*i];
            }
        }
    }

    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    
    
        for(int j=0; j<im.h; j++){
            for(int k=0; k<im.w; k++){
                gray.data[k + (im.w)*j] = 0.299*im.data[k + (im.w)*j] + 0.587* im.data[k + (im.w)*j +(im.w)*(im.h)] + 0.114*im.data[k + (im.w)*j + (im.w)*(im.h)*2];
            }
        }
    
    return gray;
}

void shift_image(image im, int c, float v)
{
    
        for(int j=0; j<im.h; j++){
            for(int k=0; k<im.w; k++){
                im.data[k + (im.w)*j + (im.w)*(im.h)*c] += v;
            }
        }
    
}

void clamp_image(image im)
{
   for(int i=0; i<im.c; i++){
        for(int j=0; j<im.h; j++){
            for(int k=0; k<im.w; k++){
                if(im.data[k + (im.w)*j + (im.w)*(im.h)*i] <0) im.data[k + (im.w)*j + (im.w)*(im.h)*i]=0;
                else if(im.data[k + (im.w)*j + (im.w)*(im.h)*i]>1) im.data[k + (im.w)*j + (im.w)*(im.h)*i]=1;
                else continue;
            }
        }
    }

}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{ //calculating value
for(int i=0; i<im.h; i++){
    for(int j=0; j<im.w; j++){
        float H,S,V,H1;
        float R=im.data[j+ i*im.w], G=im.data[j+i*im.w+im.h*im.w], B=im.data[j+i*im.w+2*im.h*im.w];
     V=three_way_max(R, G, B );
    float m=three_way_min(R, G, B);

//calculating saturation

    if((R == 0) && (G==0) && (B==0)) { S = 0;}
    else { S = (V-m)/V;}

//calculating hue
    if(V==m) { H = 0;}
    else if(V-m!=0){
        if(V==R){
             H1 = (G-B)/(V-m);
            if(H1<0) { H = H1/6 + 1;}
            else { H = H1/6;}
        }
        else if(V == G){
             H1 = (B-R)/(V-m) + 2;
            if(H1<0) { H = H1/6 + 1;}
            else { H = H1/6;}
        }
        else if(V== B){
             H1 = (R-G)/(V-m) + 4;
            if(H1<0) { H = H1/6 + 1;}
            else { H = H1/6;}
        }
    }
    im.data[j+ i*im.w]=H;
    im.data[j+ i*im.w+ im.h*im.w]=S;
    im.data[j+ i*im.w+ 2*im.h*im.w]=V;


    }
}
    

}

void hsv_to_rgb(image im)
{
    for(int i=0; i<im.h; i++){
      for(int j=0; j<im.w; j++){
        float R,G,B;
        float H =im.data[j+ i*im.w] , S = im.data[j+ i*im.w+ im.h*im.w], V = im.data[j+ i*im.w+ 2*im.h*im.w];
        float H1=6*H;
        int p=floor(H1);
        float F=H1-p;
        float m=V*(1-S);
        float n=V*(1-S*F);
        float k=V*(1-S*(1-F));
        switch(p){
            case 0: R=V;
                    G=k;
                    B=m;
                    break;

            case 1: R=n;
                    G=V;
                    B=m;
                    break;

            case 2: R=m;
                    G=V;
                    B=k;
                    break;
            case 3: R=m;
                    G=n;
                    B=V;
                    break;
            case 4: R=k;
                    G=m;
                    B=V;
                    break;
            case 5: R=V;
                    G=m;
                    B=n;
                    break;


                    

        }
    im.data[j+ i*im.w]=R;
    im.data[j+ i*im.w+ im.h*im.w]=G;
    im.data[j+ i*im.w+ 2*im.h*im.w]=B;


      }
    }
    
}

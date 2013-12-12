/* compiles with command line  g++ Segment.c -lX11 -lm -L/usr/X11R6/lib -o Segment  */

//#include <iostream>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <math.h>
//#include <cstdlib>
#include <algorithm>
#include <vector>
#define IN 9999
//#define N 6
using namespace std;

Display *display_ptr;
Screen *screen_ptr;
int screen_num;
char *display_name = NULL;
unsigned int display_width, display_height;

Window win;
int border_width;
unsigned int win_width, win_height;
int win_x, win_y;
int x,y,q,i,j,k,b,r=1,range =100,z=0,line_count=0,finish,Z;
int data[200][200];
char line[128];

int x_arr[2000], y_arr[2000],final[2000], d1, d2, d3, d4, m1, m2, m3, m4,lins=1,lins1,counter=1,h=1,mm=0;
int click=0,oldx,oldy,finalM,finalN;
int dist1[5000000];
			
int dist;
bool line_intersect;

XWMHints *wm_hints;
XClassHint *class_hints;
XSizeHints *size_hints;
XTextProperty win_name, icon_name;
char *win_name_string = "Shortest Path Program";
char *icon_name_string = "Icon for Example Window";

XEvent report;
GC gc, gc_yellow, gc_red, gc_grey,gc_green;
unsigned long valuemask = 0;
XGCValues gc_values, gc_yellow_values,gc_green_values, gc_red_values, gc_grey_values;
Colormap color_map;
XColor tmp_color1, tmp_color2;


class Vector
{
public:
    float x_, y_;

    Vector(float f = 0.0f)
        : x_(f), y_(f) {}

    Vector(float x, float y)
        : x_(x), y_(y) {}
};
//////////////////////////////////////////////////////////////// line Segment////////////////////////////////////
class LineSegment
{
public:
    Vector begin_;
    Vector end_;

    LineSegment(const Vector& begin, const Vector& end)
        : begin_(begin), end_(end) {}

    enum IntersectResult { PARALLEL, COINCIDENT, NOT_INTERESECTING, INTERESECTING };

    IntersectResult Intersect(const LineSegment& other_line, Vector& intersection)
    {
        float denom = ((other_line.end_.y_ - other_line.begin_.y_)*(end_.x_ - begin_.x_)) -
                      ((other_line.end_.x_ - other_line.begin_.x_)*(end_.y_ - begin_.y_));

        float nume_a = ((other_line.end_.x_ - other_line.begin_.x_)*(begin_.y_ - other_line.begin_.y_)) -
                       ((other_line.end_.y_ - other_line.begin_.y_)*(begin_.x_ - other_line.begin_.x_));

        float nume_b = ((end_.x_ - begin_.x_)*(begin_.y_ - other_line.begin_.y_)) -
                       ((end_.y_ - begin_.y_)*(begin_.x_ - other_line.begin_.x_));

        if(denom == 0.0f)
        {
            if(nume_a == 0.0f && nume_b == 0.0f)
            {
                return COINCIDENT;
            }
            return PARALLEL;
        }

        float ua = nume_a / denom;
        float ub = nume_b / denom;

        if(ua >= 0.0f && ua <= 1.0f && ub >= 0.0f && ub <= 1.0f)
        {
            // Get the intersection point.
            intersection.x_ = begin_.x_ + ua*(end_.x_ - begin_.x_);
            intersection.y_ = begin_.y_ + ua*(end_.y_ - begin_.y_);

            return INTERESECTING;
        }

        return NOT_INTERESECTING;
    }
};

void DoLineSegmentIntersection(const Vector& p0, const Vector& p1, const Vector& p2, const Vector& p3)
{
    LineSegment linesegment0(p0, p1);
    LineSegment linesegment1(p2, p3);

    Vector intersection;

    std::cout << "Line Segment 0: (" << p0.x_ << ", " << p0.y_ << ") to (" << p1.x_ << ", " << p1.y_ << ")\n"
              << "Line Segment 1: (" << p2.x_ << ", " << p2.y_ << ") to (" << p3.x_ << ", " << p3.y_ << ")\n";

    switch(linesegment0.Intersect(linesegment1, intersection))
    {
    case LineSegment::PARALLEL:
        std::cout << "The lines are parallel\n\n";
	line_intersect=false; 		
	counter=1;        
	break;
    case LineSegment::COINCIDENT:
        std::cout << "The lines are coincident\n\n";		
	line_intersect=true;
	counter=1;         
	break;
    case LineSegment::NOT_INTERESECTING:
        std::cout << "The lines do not intersect\n\n";
	line_intersect=false;	
	counter=1;         
	break;
    case LineSegment::INTERESECTING:
        std::cout << "The lines intersect at (" << intersection.x_ << ", " << intersection.y_ << ")\n\n";	     
	

			if ((d1 == intersection.x_ and d2 == intersection.y_) or (d3 == intersection.x_ and d4 == intersection.y_))
				{
				line_intersect=false;
				counter=counter+1;
				}			
	
			else
			{
				line_intersect=true;

              
			}	
			break;
    }
}

///////////////////////////////////////////////////////////////////////////// line Segment End ////////////////////////////////////
///////////////
//////////////////////// Dijkestra//////////////////////////////////////

vector<int> dijkstra(int cost[500][500], int source, int target);

vector<int> startPoint;
vector<int> dijsktra(int cost[500][500],int source,int target)
{
    int dist[500],prev[500],selected[500]={0},i,m,min,start,d,j;
    char path[500];
    char revspath[500];
    for(i=1;i< Z;i++)

    {

        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;

    dist[start] = 0;
    while(selected[target] ==0)
    {
      
        min = IN;
        m = 0;
        for(i=1;i< Z;i++)
        {
            d = dist[start] +cost[start][i];
	
            if(d< dist[i]&&selected[i]==0)
            {
                dist[i] = d;
                prev[i] = start;
           
}

            if(min>dist[i] && selected[i]==0)
            {
                min = dist[i];
                m = i;

            }
        }
        start = m;

        selected[start] = 1;

  }
 
{

int i=0,j=0;



    
    start = target;
    j = 0;
    while(start != -1)
    {
        path[j++] = start+65;
	;
        start = prev[start];
	if(start!=-1) {
	printf("starting position is %d\n",start) ;
	startPoint.push_back(start) ;
	final[r]=start; 
	r=r+1;
	}
    }

	}
    
    return startPoint ;//dist[target];
}
///////////////////////////////////////////////////////// Dijkestra end///////////////////////////////

   



/////////////////////////////////////////////////


int main(int argc, char **argv)
{
  /* opening display: basic connection to X Server */
  if( (display_ptr = XOpenDisplay(display_name)) == NULL )
    { printf("Could not open display. \n");// exit(-1);
      
    }
  printf("Connected to X server  %s\n", XDisplayName(display_name) );
  screen_num = DefaultScreen( display_ptr );
  screen_ptr = DefaultScreenOfDisplay( display_ptr );
  color_map  = XDefaultColormap( display_ptr, screen_num );
  display_width  = DisplayWidth( display_ptr, screen_num );
  display_height = DisplayHeight( display_ptr, screen_num );

  printf("Width %d, Height %d, Screen Number %d\n", 
           display_width, display_height, screen_num);
  /* creating the window */
  border_width = 10;
  win_x = 0; win_y = 0;
  win_width = display_width/2;
  win_height = (int) (win_width / 1.2); /*rectangular window*/
  
  win= XCreateSimpleWindow( display_ptr, RootWindow( display_ptr, screen_num),
                            win_x, win_y, win_width, win_height, border_width,
                            BlackPixel(display_ptr, screen_num),
                            WhitePixel(display_ptr, screen_num) );
  /* now try to put it on screen, this needs cooperation of window manager */
  size_hints = XAllocSizeHints();
  wm_hints = XAllocWMHints();
  class_hints = XAllocClassHint();
  if( size_hints == NULL || wm_hints == NULL || class_hints == NULL )
    { printf("Error allocating memory for hints. \n"); 
    //exit(-1);
    }

  size_hints -> flags = PPosition | PSize | PMinSize  ;
  size_hints -> min_width = 60;
  size_hints -> min_height = 60;

  XStringListToTextProperty( &win_name_string,1,&win_name);
  XStringListToTextProperty( &icon_name_string,1,&icon_name);
  
  wm_hints -> flags = StateHint | InputHint ;
  wm_hints -> initial_state = NormalState;
  wm_hints -> input = False;

  class_hints -> res_name = "x_use_example";
  class_hints -> res_class = "examples";

  XSetWMProperties( display_ptr, win, &win_name, &icon_name, argv, argc,
                    size_hints, wm_hints, class_hints );

  /* what events do we want to receive */
  XSelectInput( display_ptr, win, 
            ExposureMask | StructureNotifyMask | ButtonPressMask );
  
  /* finally: put window on screen */
  XMapWindow( display_ptr, win );

  XFlush(display_ptr);

  /* create graphics context, so that we may draw in this window */
  gc = XCreateGC( display_ptr, win, valuemask, &gc_values);
  XSetForeground( display_ptr, gc, BlackPixel( display_ptr, screen_num ) );
  XSetLineAttributes( display_ptr, gc, 4, LineSolid, CapRound, JoinRound);
  /* and three other graphics contexts, to draw in yellow and red and grey*/
  
 gc_yellow = XCreateGC( display_ptr, win, valuemask, &gc_yellow_values);
  XSetLineAttributes(display_ptr, gc_yellow, 2, LineSolid,CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "yellow", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color yellow\n"); 
    //exit(-1);
    } 
  else
    XSetForeground( display_ptr, gc_yellow, tmp_color1.pixel );

 gc_green = XCreateGC( display_ptr, win, valuemask, &gc_green_values);
 XSetLineAttributes( display_ptr, gc_green, 2, LineSolid, CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "green", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color green\n"); 
    //exit(-1);
    } 
  else
    XSetForeground( display_ptr, gc_green, tmp_color1.pixel );  
 
  gc_red = XCreateGC( display_ptr, win, valuemask, &gc_red_values);

  XSetLineAttributes( display_ptr, gc_red, 3, LineSolid, CapRound, JoinRound);
  if( XAllocNamedColor( display_ptr, color_map, "red", 
			&tmp_color1, &tmp_color2 ) == 0 )
    {printf("failed to get color red\n"); //exit(-1);
      
    } 
  else
    XSetForeground( display_ptr, gc_red, tmp_color1.pixel );

  gc_grey = XCreateGC( display_ptr, win, valuemask, &gc_grey_values);
  if( XAllocNamedColor( display_ptr, color_map, "light grey", 
			&tmp_color1, &tmp_color2 ) == 0 )

    {printf("failed to get color grey\n");
  //exit(-1);
      
    } 
  else
{
    XSetForeground( display_ptr, gc_grey, tmp_color1.pixel );
}




 if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
    }
    else
    {
        // We assume argv[1] is a filename to open
        FILE *file = fopen( argv[1], "r" );

        /* fopen returns 0, the NULL pointer, on failure */
        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else
        {
           int i=0;
           line[0] = 0;
           while(fgets(line,sizeof(line),file))
            {
               sscanf(line, "S (%d,%d)(%d,%d)", &data[i][0], &data[i][1], &data[i][2], &data[i][3]);
               printf("%d,%d,%d,%d\n", data[i][0], data[i][1], data[i][2], data[i][3]);
 int count=1,k=1;   
   for (i=0; i <= count; i++)
       {
         while(fscanf(file, "S (%d,%d)(%d,%d)\n", &data[i][0], &data[i][1], &data[i][2], &data[i][3]) !=EOF)
         {

		d1=data[i][0];
		x_arr[k]=d1;
		d2=data[i][1];
		y_arr[k]=d2;
		d3=data[i][2];
		x_arr[k+1]=d3;
		d4=data[i][3];
		y_arr[k+1]=d4;
		k=k+2;

	 		XDrawLine(display_ptr, win, gc_red, d1, d2,
                     		d3, d4 );
		lins=lins+1;
		 count=count+1;

}
	}
	              
               i=i+1;
            }

            fclose( file );

        }
      }


lins=lins-1;

  /* and now it starts: the event loop */
  while(1)
    { XNextEvent( display_ptr, &report );
      switch( report.type )
	{
	case Expose:
          /* (re-)draw the example figure. This event happens
             each time some part ofthe window gets exposed (becomes visible) */
		  
          break;
        case ConfigureNotify:
          /* This event happens when the user changes the size of the window*/
          win_width = report.xconfigure.width;
          win_height = report.xconfigure.height;
          break;
        case ButtonPress:
          /* This event happens when the user pushes a mouse button. I draw
            a circle to show the point where it happened, but do not save 
            the position; so when the next redraw event comes, these circles
	    disappear again. */
          {  
             //int x, y;
  	     x = report.xbutton.x;
             y = report.xbutton.y;

            
if (report.xbutton.button == Button1 )
{      
  XFillArc( display_ptr, win, gc_red, 
                       x -win_height/80, y- win_height/80,
                       win_height/40, win_height/40, 0, 360*64);




if (click == 0)	
{
oldx=x;
oldy=y;
click=click+1;
}
else if (click == 1)

{
	finalM=x;
	finalN=y;
	finish =((2*lins)+2);
	Z=finish+1;
	dist1[0]='\0';
	h=1;

for(i=1;i<finish;i++)
{
		if (i == 1)
		{
			d1=oldx;
			d2=oldy;
		}
		else 
		{
			d1=x_arr[i-1];
			d2=y_arr[i-1];

		}

for(j=i+1;j<finish+1;j++)
{
line_intersect=false;
////////////////////////////////////////////////////////

		if (j == 2)
		{
		}
		else

		{
		if ((i == (j-1)) and ( j % 2 == 1))
		{
		j = j+1;
		}
		
		}
	
/////////////////////////////////////////////////////
		if (j == finish)
		{
			d3=x;
			d4=y;
		}

		else
		{
			d3=x_arr[j-1];
			d4=y_arr[j-1];

		}

for(int z=1;z<finish;z++)
{		
qw:
	
			m1=x_arr[z];
			m2=y_arr[z];						
			m3=x_arr[z+1];
			m4=y_arr[z+1];
			z=z+1;
			if (m4 == 0)
			{	
			break;
			}
			if ((m1 == d1) and (m2 == d2) and (m3 == d3) and (m4 == d4))
	 		{ 
				z=z+1;		 
		 		goto qw; 
		 	}

			if (line_intersect == false) 
			{ 
					DoLineSegmentIntersection(Vector(d1,d2), Vector(d3,d4), Vector(m1,m2), Vector(m3,m4)); 
				}
			if (((m1 == d1) and (m2 == d2)) or ((m1 == d3) and (m2 == d4))or ((m3 == d3) and (m4 == d4)) or ((m3 == d1) and (m4 == d2))) 
		 		{ 
		 			z=z+1;		 
		 		goto qw; 
		 		} 
 
}
				if (((d1 == 0) && (d2 == 0)) || ((d3 == 0) && (d4 == 0)))
				{					
					line_intersect == true;
				}
	
		if (line_intersect == false)
		{		
			XDrawLine(display_ptr, win, gc_yellow, d1, d2,d3, d4);
			line_intersect=false;
			dist=sqrt(((d1-d3)*(d1-d3))+((d2-d4)*(d2-d4)));

			
					
		dist1[h]=i;
			h=h+1;
		dist1[h]=j;
			h=h+1;
		dist1[h]=dist;
			h=h+1;
		}

/////////////////////////////////////// For DIJKSRTRA's ALGORITHM calculation ////////////////////////////////////////////

}			
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////  Shortest Path Calculated
/////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

//N=finish;
 vector<int> stPoint;
    int cost[500][500],w,ch,co;
    int source, target,x,y;
    int start[500][500];
	h=1;
    printf("\tShortest Path Algorithm(DIJKSRTRA's ALGORITHM)\n");
    for(i=1;i< Z;i++)
    for(j=0;j< Z;j++)
    cost[i][j] = IN;
    for(x=1;x< Z;x++)
    {
	
        for(y=x+1;y< Z;y++)

        {
int oldu,oldv;
	oldu=x;
	oldv=y;

	x=dist1[h];
	y=dist1[h+1];
	w=dist1[h+2];

	if (x == oldu and y == oldv)
	{
		w == dist1[h+2];

		h=h+3;
	}
	else if (x>=oldu and y>=oldv)
	{
		w=10000000;
		x=oldu;
		y=oldv;
	}
	else if (x<=oldu and y<=oldv)
	{
		w=10000000;
		x=oldu;
		y=oldv;
	}
	else if (x<=oldu and y>=oldv)
	{
		w=100000000;
		x=oldu;
		y=oldv;
	}
	else if (x>=oldu and y<=oldv)
	{
		w=100000000;
		x=oldu;
		y=oldv;
	}   
	       
		cost [x][y] = cost[y][x] = w;


        }

        printf("\n");

    }  
	source=1;
	target=((2*lins)+2);

    stPoint = dijsktra(cost,source,target);	
    
    vector<int>::reverse_iterator rit;
    for(rit=stPoint.rbegin(); rit<stPoint.rend();++rit) {
    printf("Start point of the next path is %d", *rit) ;
    printf("\n") ;
	
	
    } 
	r=r-1;

///////////////////////////////////////////
///////////
////////// shortest path draw line////////
//////////
	

	for(int k=1;k<=r;k++)
	{
	
	 b=final[k];
	if (k == 1)
		{
		d1=finalM;
		d2=finalN;
	 	}
	if (k == r)
		{
		d3=oldx;
		d4=oldy;
		}
	else
		{
		d3=x_arr[b-1];
		d4=y_arr[b-1];
		}
		

	 		XDrawLine(display_ptr, win, gc_green, d1, d2,
                   		d3, d4 );
		d1=d3;
		d2=d4;


}

	
click=click+1;
}
else
{
int rom;
rom=2*lins;
XClearWindow(display_ptr, win);
   for(k=1;k<=rom;k++)
       {
		d1=x_arr[k];
		d2=y_arr[k];
		d3=x_arr[k+1];
		d4=y_arr[k+1];

	 		XDrawLine(display_ptr, win, gc_red, d1, d2,
                     		d3, d4 );
		k=k+1;

	}

click=0;
b=0; 
k=0; 
r=1; 
h=1; 
final[0]='\0';
}

} 
            else
	       exit(0);
                 
              
				

}

       

          break;

		//Draw All reachable Path
		
                // XDrawLine(display_ptr, win, gc, xmine7, ymine7, xmine8, ymine8);
		  
        default:
	  /* this is a catch-all for other events; it does not do anything.
             One could look at the report type to see what the event was */ 
          break;


		}
	}



    }





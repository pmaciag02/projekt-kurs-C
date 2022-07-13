#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <gtk/gtk.h>


GtkWidget *button[10][10], *image[4], *number, *text, *grid, *grid2, *points;
char *discription;
int game_board[10][10], next_colours[5], n, random1, random2, random3, free_count, k1=0, k2=0, clicked=0, t[10][10], points_count=0;

char colours[10][20]= {"kolor/frame.png","kolor/dgreen.png","kolor/blue.png","kolor/red.png","kolor/yellow.png","kolor/pink.png","kolor/navyblue.png","kolor/green.png"};
char colours_clicked[10][20]= {"kolor/frame.png","kolor/dgreen2.png","kolor/blue2.png","kolor/red2.png","kolor/yellow2.png","kolor/pink2.png","kolor/navyblue2.png","kolor/green2.png"};




struct list
{
    int val;
    struct list *next;
} List;



struct list *free_board;


void init(struct list *free_board)
{

    for(int i=1; i<free_count; i++)
    {
        free_board->next=malloc(sizeof(List));
        free_board=free_board->next;
        free_board->val=i;
        free_board->next=NULL;
    }
}


void random_colour()
{
    random1=rand()%7;
    random1++;
    random2=rand()%7;
    random2++;
    random3=rand()%7;
    random3++;
    gtk_image_set_from_file (GTK_IMAGE(image[0]),colours[random1]);
    gtk_image_set_from_file (GTK_IMAGE(image[1]),colours[random2]);
    gtk_image_set_from_file (GTK_IMAGE(image[2]),colours[random3]);

}


void endgame()
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"KONIEC");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 50);
    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *Box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *Box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(window), Box1);

    GtkWidget *koniec = gtk_label_new("KONIEC");
    GtkWidget *wynik = gtk_label_new("Zdobyte punkty:");


    char liczba[10];
    sprintf(liczba, "%d", points_count);
    printf("%s\n", liczba);
    GtkWidget *pkt=gtk_label_new(liczba);


    gtk_box_pack_start(GTK_BOX(Box1), koniec, TRUE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(Box2), wynik, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(Box2), pkt, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(Box1), Box2, TRUE, FALSE, 0);


    GtkWidget *close = gtk_button_new_with_label("Zakoncz gre");
    g_signal_connect(G_OBJECT(close), "clicked",G_CALLBACK(gtk_main_quit), NULL);

    gtk_box_pack_start(GTK_BOX(Box1), close, TRUE, FALSE, 10);
    gtk_widget_show_all(window);
}



int remove_random(struct list *free_board)
{
    if(free_count==1)
    {
        free_count=0;
        int a=(free_board->val)/9;
        int b=(free_board->val)%9;
        free(free_board);
        return (a*10)+b;
    }
    int x=rand()%free_count;
    for(int i=1; i<x; i++)
    {
        free_board=free_board->next;
    }

    int a=(free_board->next->val)/9;
    int b=(free_board->next->val)%9;

    free_count--;

    if(free_board->next->next==NULL)
    {
        free_board->next=NULL;
    }
    else
    {
        struct list *temp=free_board->next->next;
        free(free_board->next);
        free_board->next=temp;
    }

    return (a*10)+b;
}









void remove_clicked(struct list *free_board, int x)
{

    if(free_count>1)
    {
        if(free_board->val!=x)
        {
            while(free_board->next!=NULL)
            {
                if(free_board->next->val==x)break;
                free_board=free_board->next;
            }
        }
        else
        {
            struct list *temp=free_board;
            free_board=free_board->next;
            free(temp);
            free_count--;
            return;
        }


        free_count--;


        if(free_board->next->next==NULL)
        {
            free_board->next=NULL;
        }
        else
        {
            struct list *temp=free_board->next->next;
            free(free_board->next);
            free_board->next=temp;
        }
    }
    else
    {
        free(free_board);
        free_count=0;
    }
}






void add(struct list *free_board, int x)
{

    while(free_board->next!=NULL)
    {
        free_board=free_board->next;
    }

    free_board->next=malloc(sizeof(List));
    free_board=free_board->next;
    free_board->val=x;
    free_board->next=NULL;
    free_count++;
}









void add_new(int random)
{

    int a,b;

    int x=remove_random(free_board);

    a=x/10;
    b=x%10;


    game_board[a][b]=random;
    printf("Random: %d %d\n", a, b);
    GtkWidget *image = gtk_image_new_from_file (colours[random]);
    gtk_button_set_image(GTK_BUTTON (button[a][b]), image);

}


void ways(int a, int b)
{
    t[a][b]=1;
    if(a>0 && game_board[a-1][b]==0 && t[a-1][b]==0)
    {
        ways(a-1,b);
    }
    if(a<n-1 && game_board[a+1][b]==0 && t[a+1][b]==0)
    {
        ways(a+1,b);
    }
    if(b>0 && game_board[a][b-1]==0 && t[a][b-1]==0)
    {
        ways(a,b-1);
    }
    if(b<n-1 && game_board[a][b+1]==0 && t[a][b+1]==0)
    {
        ways(a,b+1);
    }
}




void check_points()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%d ", game_board[i][j]);
        }
        putchar('\n');
    }
    int over=0;
    int k, colour;
    for(int i=0; i<n; i++)
    {
        if(over) break;
        for(int j=0; j<n; j++)
        {
            if(game_board[i][j])
            {

                int counter=1;
                if(i>=0 && i<=4)
                {
                    for(int k=1; k<5; k++)
                    {
                        if(game_board[i+k][j]==game_board[i][j])
                        {
                            counter++;
                        }
                    }
                    if(counter==5)
                    {
                        k=0;
                        colour=game_board[i][j];

                        while(i+k<n && game_board[i+k][j]==colour)
                        {
                            GtkWidget *image = gtk_image_new_from_file (colours[0]);
                            gtk_button_set_image(GTK_BUTTON (button[i+k][j]), image);
                            game_board[i+k][j]=0;
                            add(free_board, ((i+k)*9)+j);
                            k++;
                            points_count++;
                        }
                        over=1;
                        break;
                    }
                }
                counter=1;
                if(i>=4 && i<=8)
                {
                    for(int k=1; k<5; k++)
                    {
                        if(game_board[i-k][j]==game_board[i][j])
                        {
                            counter++;
                        }
                    }
                    if(counter==5)
                    {
                        k=0;
                        colour=game_board[i][j];
                        while(i-k>=0 && game_board[i-k][j]==colour)
                        {
                            GtkWidget *image = gtk_image_new_from_file (colours[0]);
                            gtk_button_set_image(GTK_BUTTON (button[i-k][j]), image);
                            game_board[i-k][j]=0;
                            add(free_board, ((i-k)*9)+j);
                            k++;
                            points_count++;
                        }
                        over=1;
                        break;
                    }
                }
                counter=1;
                if(j>=0 && j<=4)
                {
                    for(int k=1; k<5; k++)
                    {
                        if(game_board[i][j+k]==game_board[i][j])
                        {
                            counter++;
                        }
                    }
                    if(counter==5)
                    {
                        k=0;
                        colour=game_board[i][j];
                        while((j+k)<n && game_board[i][j+k]==colour)
                        {
                            GtkWidget *image = gtk_image_new_from_file (colours[0]);
                            gtk_button_set_image(GTK_BUTTON (button[i][j+k]), image);
                            game_board[i][j+k]=0;
                            add(free_board, (i*9)+j+k);
                            k++;
                            points_count++;
                        }
                        over=1;
                        break;
                    }
                }
                counter=1;
                if(j>=4 && j<=8)
                {
                    for(int k=1; k<5; k++)
                    {
                        if(game_board[i][j-k]==game_board[i][j])
                        {
                            counter++;
                        }
                    }
                    if(counter==5)
                    {
                        k=0;
                        colour=game_board[i][j];
                        while(j-k>=0 && game_board[i][j-k]==colour)
                        {
                            GtkWidget *image = gtk_image_new_from_file (colours[0]);
                            gtk_button_set_image(GTK_BUTTON (button[i][j-k]), image);
                            game_board[i][j-k]=0;
                            add(free_board, (i*9)+j-k);
                            k++;
                            points_count++;
                        }
                        over=1;
                        break;
                    }

                }
                counter=1;
                if(i<=4 && j<=4)
                {
                    for(int k=1; k<5; k++)
                    {
                        if(game_board[i+k][j+k]==game_board[i][j])
                        {
                            counter++;
                        }
                    }
                    if(counter==5)
                    {
                        k=0;
                        colour=game_board[i][j];
                        while(j+k<=8 && i+k<=8 && game_board[i+k][j+k]==colour)
                        {
                            GtkWidget *image = gtk_image_new_from_file (colours[0]);
                            gtk_button_set_image(GTK_BUTTON (button[i+k][j+k]), image);
                            game_board[i+k][j+k]=0;
                            add(free_board, ((i+k)*9)+j+k);
                            k++;
                            points_count++;
                        }
                        over=1;
                        break;
                    }

                }
                counter=1;
                if(i<=4 && j>=4)
                {
                    for(int k=1; k<5; k++)
                    {
                        if(game_board[i+k][j-k]==game_board[i][j])
                        {
                            counter++;
                        }
                    }
                    if(counter==5)
                    {
                        k=0;
                        colour=game_board[i][j];
                        while(j-k>=0 && i+k<=8 && game_board[i+k][j-k]==colour)
                        {
                            GtkWidget *image = gtk_image_new_from_file (colours[0]);
                            gtk_button_set_image(GTK_BUTTON (button[i+k][j-k]), image);
                            game_board[i+k][j-k]=0;
                            add(free_board, ((i+k)*9)+j-k);
                            k++;
                            points_count++;
                        }
                        over=1;
                        break;
                    }

                }
                counter=1;
                if(i>=4 && j<=4)
                {
                    for(int k=1; k<5; k++)
                    {
                        if(game_board[i-k][j+k]==game_board[i][j])
                        {
                            counter++;
                        }
                    }
                    if(counter==5)
                    {
                        k=0;
                        colour=game_board[i][j];
                        while(j+k<=8 && i-k>=0 && game_board[i-k][j+k]==colour)
                        {
                            GtkWidget *image = gtk_image_new_from_file (colours[0]);
                            gtk_button_set_image(GTK_BUTTON (button[i-k][j+k]), image);
                            game_board[i-k][j+k]=0;
                            add(free_board, ((i-k)*9)+j+k);
                            k++;
                            points_count++;
                        }
                        over=1;
                        break;
                    }

                }
                counter=1;
                if(i>=4 && j>=4)
                {
                    for(int k=1; k<5; k++)
                    {
                        if(game_board[i-k][j-k]==game_board[i][j])
                        {
                            counter++;
                        }
                    }
                    if(counter==5)
                    {
                        k=0;
                        colour=game_board[i][j];
                        while(j-k>=0 && i-k>=0 && game_board[i-k][j-k]==colour)
                        {
                            GtkWidget *image = gtk_image_new_from_file (colours[0]);
                            gtk_button_set_image(GTK_BUTTON (button[i-k][j-k]), image);
                            game_board[i-k][j-k]=0;
                            add(free_board, ((i-k)*9)+j-k);
                            k++;
                            points_count++;
                        }
                        over=1;
                        break;
                    }

                }
            }
        }
    }
    char liczba[10];
    sprintf(liczba, "%d", points_count);
    gtk_label_set_text(GTK_LABEL(points),liczba);
}




static void move(GtkWidget *widget,gpointer data)
{
    char s[5];
    strcpy(s,(gchar *)data);
    int a=s[0]-'0';//wiersz
    int b=s[1]-'0';//kolumna
    printf("%d %d\n", a, b);


    if(!clicked)
    {

        if(game_board[a][b])
        {
            printf("kolor %d\n", game_board[a][b]);
            GtkWidget *image = gtk_image_new_from_file (colours_clicked[game_board[a][b]]);
            gtk_button_set_image(GTK_BUTTON (widget), image);

            k1=a;
            k2=b;
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    t[i][j]=0;
                }
            }
            ways(a,b);
        }
        else
        {
            printf("error\n");
        }

        clicked=game_board[a][b];
    }
    else
    {
        if(!game_board[a][b] && t[a][b])
        {
            game_board[a][b]=clicked;
            GtkWidget *image = gtk_image_new_from_file (colours[clicked]);
            gtk_button_set_image(GTK_BUTTON (widget), image);
            image = gtk_image_new_from_file (colours[0]);
            gtk_button_set_image(GTK_BUTTON (button[k1][k2]), image);
            game_board[k1][k2]=0;


            if(free_board->val==(a*9)+b)
            {
                struct list *temp=free_board;
                free_board=free_board->next;
                free(temp);
                free_count--;
            }
            else
            {
                remove_clicked(free_board, (a*9)+b);
            }

            add(free_board, (k1*9)+k2);

            if(free_count<3)
            {
                endgame();
                return;
            }
            add_new(random1);
            add_new(random2);
            add_new(random3);
            random_colour();
            check_points();
            printf("Free: %d\n", free_count);
            if(free_count<3)
            {
                endgame();
                return;
            }
        }
        else
        {
            printf("error\n");
            GtkWidget *image = gtk_image_new_from_file (colours[game_board[k1][k2]]);
            gtk_button_set_image(GTK_BUTTON (button[k1][k2]), image);
            clicked=0;
        }
        clicked=0;
    }
}





int main(int argc,char *argv[])
{

    n=9;
    free_count=n*n;
    srand(time(NULL));

    gtk_init(&argc, &argv);


    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            game_board[i][j]=0;
        }
    }


    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"GTK - kulki");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(window), 50);

    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box1);





    grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    gtk_box_pack_start(GTK_BOX(box1), grid, TRUE, TRUE, 0);

    char name[100][3];


    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            game_board[i][j]=0;
            button[i][j] = gtk_button_new();
            GtkWidget *image = gtk_image_new_from_file ("kolor/frame.png");
            gtk_button_set_image(GTK_BUTTON (button[i][j]), image);
            gtk_grid_attach(GTK_GRID(grid), button[i][j], j, i, 1, 1);

            name[(i*10)+j][0]=i+'0';
            name[(i*10)+j][1]=j+'0';
            name[(i*10)+j][2]=0;

            g_signal_connect(G_OBJECT(button[i][j]), "clicked",G_CALLBACK(move), name[(i*10)+j]);
        }
    }


    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);



    discription="Następne kolory:";
    GtkWidget *button2=gtk_label_new(discription);
    gtk_box_pack_start(GTK_BOX(box2), button2, TRUE, FALSE, 10);



    grid2 = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(grid2), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid2), FALSE);
    gtk_grid_set_column_spacing(GTK_GRID(grid2), 15);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid2), FALSE);
    gtk_box_pack_start(GTK_BOX(box2), grid2, TRUE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(box1), box2, TRUE, TRUE, 50);



    GtkWidget *box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    GtkWidget *button4 = gtk_label_new("Zdobyte punkty:");
    gtk_box_pack_start(GTK_BOX(box3), button4, TRUE, FALSE, 10);

    points = gtk_label_new("0");

    gtk_box_pack_start(GTK_BOX(box3), points, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box1), box3, TRUE, TRUE, 10);





    free_board=malloc(sizeof(List));
    free_board->val=0;
    free_board->next=NULL;
    init(free_board);


    random1=rand()%7;
    random1++;
    random2=rand()%7;
    random2++;
    random3=rand()%7;
    random3++;


    image[0] = gtk_image_new_from_file (colours[random1]);
    gtk_grid_attach(GTK_GRID(grid2), image[0], 0, 0, 1, 1);
    image[1] = gtk_image_new_from_file (colours[random2]);
    gtk_grid_attach(GTK_GRID(grid2), image[1], 1, 0, 1, 1);
    image[2] = gtk_image_new_from_file (colours[random3]);
    gtk_grid_attach(GTK_GRID(grid2), image[2], 2, 0, 1, 1);



    add_new(random1);
    add_new(random2);
    add_new(random3);

    random_colour();

    gtk_widget_show_all(window);
    gtk_main();


    return 0;
}

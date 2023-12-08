#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void SetColor(int ForgC)
 {
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
typedef struct Category Category;
typedef struct Product Product;



struct Category
{
    char CategoryName[10];
    Product *prod;
    int numProduct;

};


struct Product
{
    char ProductName[10];
    int ProductPrice;
    int ProductQuantity;

};




void DisplayCategoriesAndProducts(Category *categories, int numCate)
{
        for (int i = 0; i < numCate; i++)
        {

            SetColor(12);
            printf("\n------------------------------------------- Category: %s -------------------------------------------\n", categories[i].CategoryName);

            SetColor(15);
            for (int j = 0; j < categories[i].numProduct; j++)
            {
                printf("\n Product Name: %s \n", categories[i].prod[j].ProductName);
                printf("\n Product Price: %d \n", categories[i].prod[j].ProductPrice);
                printf("\n Product Quantity: %d \n\n\n",categories[i].prod[j].ProductQuantity);


            }
            /*SetColor(12);
            printf("\n************************************************************************************************************************\n");
            SetColor(15);*/
        }

}

void MoveProduct(Category *category ,int numCat)
{
    char SourceCategory[10];
    char DestinationCategory[10];
    char ProductNameMove[10];

    if(numCat==0)
    {
        SetColor(12);
        printf("\n\n  No Category To Move Product!,Please Add Category First.");
        SetColor(15);
    }
    else
    {
        printf("\n => Enter name of category you want to move 'FROM' (Source):");
        scanf("%s",SourceCategory);
        printf("\n => Eenter name of category you want to move 'TO' (Destination):");
        scanf("%s",DestinationCategory);


        int sourceIndex=-1;
        int destinationIndex=-1;
        int productIndex=-1;

        for(int i=0; i<numCat ; i++)
        {
            if(strcmp(SourceCategory,category[i].CategoryName)==0)
            {
                sourceIndex=i;
            }
            if(strcmp(DestinationCategory,category[i].CategoryName)==0)
            {
                destinationIndex=i;

            }
        }


        if(sourceIndex != -1 && destinationIndex !=-1)
        {
            printf("\n => Enter Your Product Name You Want To Move it:");
            scanf("%s",ProductNameMove);

            for(int i=0 ;i<category[sourceIndex].numProduct;i++)
            {
                if(strcmp(ProductNameMove,category[sourceIndex].prod[i].ProductName)==0)
                {
                    productIndex=i;
                    break;
                }
            }


            if(productIndex !=-1)
            {
                category[destinationIndex].prod=realloc(category[destinationIndex].prod,(category[destinationIndex].numProduct+1) * sizeof(Product));



                category[destinationIndex].prod[category[destinationIndex].numProduct] = category[sourceIndex].prod[productIndex];
                category[destinationIndex].numProduct++;


                //remove
                for(int j=productIndex; j <category[sourceIndex].numProduct-1; j++)
                {
                    category[sourceIndex].prod[j]=category[sourceIndex].prod[j+1];
                }
                category[sourceIndex].numProduct--;
                SetColor(12);
                printf("\n------------------------------------------- Done -------------------------------------------");
                SetColor(15);

            }else
            {
                SetColor(12);
                printf("\nSorry %s Product not found in Category %s \n", ProductNameMove,SourceCategory);
                SetColor(15);
            }


        }else
        {
            SetColor(12);
            printf("\nSource or Destination not found\n");
            SetColor(15);
        }
    }

}


void Order(Category *category ,int numCat)
{

    char buyCategoryName[10];
    char buyProductName[10];
    int numProductBuy=0;
    int numCategoryBuy=0;
    int Quantityofproduct=0;

    if(numCat==0)
    {
        SetColor(12);
        printf("\n\n No Category to do Order!,Please Add Category First. ");
        SetColor(15);
    }else
    {
        float totalCost = 0;
        printf("\n => Enter Count of Category you want to buy from: ");
        scanf("%d",&numCategoryBuy);

        if(numCategoryBuy>numCat)
        {
            printf("\n\n Only exist %d Category.",numCat);
        }
        else
        {



        for(int i=0;i<numCategoryBuy;i++)
        {
            printf("\n => Enter Category you want to buy from it: ");
            scanf("%s",buyCategoryName);
            int indexCategory=-1;


            for(int i=0;i<numCat;i++)
            {
                if(strcmp(buyCategoryName,category[i].CategoryName)==0)
                {
                    indexCategory=i;
                }

            }

            if(indexCategory !=-1)
            {
                printf("\n    -> Enter count of product you want to buy: ");
                scanf("%d",&numProductBuy);


                for(int i=0; i<numProductBuy;i++)
                {
                    printf("\n    -> Enter your product name you want to buy: ");
                    scanf("%s",buyProductName);

                    int indexProduct=-1;

                    for(int j =0;j<category[indexCategory].numProduct;j++)
                    {
                        if(strcmp(buyProductName,category[indexCategory].prod[j].ProductName)==0)
                        {
                            indexProduct=j;

                        }
                    }
                    if(indexProduct!=-1)
                    {
                        printf("\n    -> Enter Quantity you want to buy :");
                        scanf("%d",&Quantityofproduct);
                        float productCost=0;

                        if (Quantityofproduct > 0)
                        {
                            if(Quantityofproduct <= category[indexCategory].prod[indexProduct].ProductQuantity)
                            {
                                category[indexCategory].prod[indexProduct].ProductQuantity -= Quantityofproduct;
                                SetColor(12);
                                printf("\n  Your purchase has been completed   \n");
                                SetColor(15);

                                productCost=category[indexCategory].prod[indexProduct].ProductPrice * Quantityofproduct;

                                 printf("\n  Category: %s , Product: %s ,Product Quantity: %d ,Product Price: %d ,Total Price: %0.2f \n",
                                   category[indexCategory].CategoryName,category[indexCategory].prod[indexProduct].ProductName,
                                   Quantityofproduct,category[indexCategory].prod[indexProduct].ProductPrice,productCost);

                                SetColor(12);
                                printf("\n**********************************************************************************************************************\n");
                                SetColor(15);
                                totalCost += productCost;



                            }
                            else
                            {
                                SetColor(12);
                                printf("\n  \n** Not all quantities are available, available only %d\n", category[indexCategory].prod[indexProduct].ProductQuantity);
                                SetColor(15);

                            }

                        }

                        else
                        {


                            printf("\n Quantity is sold out\n");


                        }

                    }else
                    {
                        SetColor(12);
                        printf("\n Product not found \n");
                        SetColor(15);


                    }

                }

                SetColor(12);
                printf("\n\n-------------------------------------------- Your Bill --------------------------------------------\n");
                SetColor(15);
                //printf("\nTotal Cost is %.2f\n", totalCost);


            }else
            {

                SetColor(12);
                printf("\n  Category not found.\n");
                SetColor(15);
            }
            printf("\n  Total Cost is %.2f\n", totalCost);

        }
    }
    }



}

void RemoveProduct(Category *category,int numCat)
{
    if(numCat==0)
    {
        SetColor(12);
        printf("\n\n No Category to Remove! Please Add Category First.");
        SetColor(15);
    }
    else
    {
        char NameCategoryRemove[10];
        char NameProductRempve[10];

        printf("\n  Enter name of Category you want to remove from: ");
        scanf("%s",NameCategoryRemove);

        int CategoryIndexRemove =-1;


        for(int i=0; i<numCat; i++)
        {

            if(strcmp(NameCategoryRemove,category[i].CategoryName)==0)
            {
                CategoryIndexRemove=i;
                break;
            }

        }

        if(CategoryIndexRemove !=-1)
        {
            int numProductRemove=0;
            printf("\n  Enter Count of product to remove: ");
            scanf("%d",&numProductRemove);

            if(numProductRemove>category[CategoryIndexRemove].numProduct)
            {
                SetColor(12);
                printf("\n\n  Only %d products in this Category ",category[CategoryIndexRemove].numProduct);
                SetColor(15);
            }else
            {

                for(int i=0; i<numProductRemove; i++)
                {
                    printf("\n  Enter Name of product to remove: ");
                    scanf("%s",NameProductRempve);
                     int ProductIndexRemove =-1;

                    for(int j=0; j<category[CategoryIndexRemove].numProduct; j++)
                    {
                        if(strcmp(NameProductRempve,category[CategoryIndexRemove].prod[j].ProductName)==0)
                        {
                            ProductIndexRemove=j;
                            break;
                        }
                    }

                    if(ProductIndexRemove !=-1)
                    {
                        for(int k=ProductIndexRemove; k< category[CategoryIndexRemove].numProduct - 1;k++)
                        {
                            category[CategoryIndexRemove].prod[k]=category[CategoryIndexRemove].prod[k+1];
                        }
                        category[CategoryIndexRemove].numProduct--;
                        SetColor(12);
                        printf("\n-------------------------------------------Done-------------------------------------------\n");
                        SetColor(15);


                    }else
                    {
                        SetColor(12);
                        printf("\n %s Product not found in Category %s \n", NameProductRempve,NameCategoryRemove);
                        SetColor(15);
                    }
                }
            }


        }else
        {
            SetColor(12);
            printf("\n %s Category Not Found ",NameCategoryRemove);
            SetColor(15);

        }
    }
}






int main()
{
   Category *Cat = NULL;

    int SelectChoice = 0;

    int totalnumcat = 0;




    while (1)
    {

        system("cls");


        SetColor(19);
        printf("\n\n\n            *********************************************************************************\n\n");
        gotoxy(10,1);
        printf("Menu :\n");
        SetColor(10);

        for (int i = 1; i <= 6; i++)
        {
            gotoxy(15, 4 + i);
            if (i == SelectChoice)
            {
                SetColor(19);//19 blue
                printf("=> ");
            }
            else
            {
                SetColor(15);
                printf(" ");
            }

            switch (i)
            {
            case 1:
                printf("1) Add Categories and Products\n");
                break;
            case 2:
                printf("2) Display Categories and products\n");
                break;
            case 3:
                printf("3) Move Product to another Category\n");
                break;
            case 4:
                printf("4) Make Order\n");
                break;
            case 5:
                printf("5) Remove Products from Categories\n ");
                break;

            case 6:
                printf("6) Exit\n");
                SetColor(15);
            }
        }

        SetColor(19);
        printf("\n\n           *********************************************************************************\n\n");
        SetColor(15);
        char ch = getch();

        switch (ch)
        {
        case 72:
            if (SelectChoice < 1)
            {
                SelectChoice = 5;
            }
            else
            {
                SelectChoice--;
            }
            break;

        case 80:
            if (SelectChoice > 5)
            {
                SelectChoice = 1;
            }
            else
            {
                SelectChoice++;
            }
            break;

        case 13:
            switch (SelectChoice)
            {
            case 1:
               system("cls");
                int numCategory = 0;
                int numProduct = 0;

                printf("\n Do you want to add a new category? 'OR' Add Product in  Category Already exists? \n\n  (1 => NEW CATEGORY , 2 => CATEGORY EXISTS ):  ");
                int x = 0;
                scanf("%d", &x);

                if (x == 1)
                {
                    printf("\n   =>Enter number of categories: ");
                    scanf("%d", &numCategory);
                    printf("\n   =>Enter number of products: ");
                    scanf("%d", &numProduct);

                    Cat = realloc(Cat, (totalnumcat + numCategory) * sizeof(Category));


                    for (int i = totalnumcat; i < totalnumcat + numCategory; i++)
                    {
                        printf("\n********************************************************************\n");
                        SetColor(12);
                        printf("\n           Enter Category name:  ");
                        SetColor(15);


                        scanf("%s", Cat[i].CategoryName);
                        printf("\n********************************************************************\n");

                        Cat[i].prod = malloc(numProduct * sizeof(Product));

                        for (int j = 0; j<numProduct; j++)
                        {

                            printf("\n       Product %d For %s\n",j+1,Cat[i].CategoryName);
                            printf("\n Enter Product Name For %s:  ",Cat[i].CategoryName);
                            scanf("%s",Cat[i].prod[j].ProductName);
                            printf("\n Enter Product Price For %s: ",Cat[i].CategoryName);
                            scanf("%d",&Cat[i].prod[j].ProductPrice);
                            while(Cat[i].prod[j].ProductPrice <= 0)
                            {
                                SetColor(12);
                                printf("\n price invalid. Please Enter Positive Value.\n");
                                SetColor(15);
                                printf("\n Enter Product Price For %s: ",Cat[i].CategoryName);
                                scanf("%d",&Cat[i].prod[j].ProductPrice);
                            }

                            printf("\n Enter Product Quantity For %s:  ",Cat[i].CategoryName);
                            scanf("%d",&Cat[i].prod[j].ProductQuantity);
                            while(Cat[i].prod[j].ProductQuantity <= 0)
                            {
                                SetColor(12);
                                printf("\n Quantity invalid. Please Enter Positive Value.\n");
                                SetColor(15);
                                printf("\n Enter Product Quantity For %s:  ",Cat[i].CategoryName);
                                scanf("%d",&Cat[i].prod[j].ProductQuantity);
                            }


                            for(int k=0; k<j; k++)
                            {
                                if(strcmp(Cat[i].prod[j].ProductName, Cat[i].prod[k].ProductName) == 0)
                                {
                                    SetColor(12);
                                    printf("\n\n  Sorry, this product already exists in the category.\n");
                                    SetColor(15);
                                    j--; //to enter another name
                                }
                            }
                        }

                        Cat[i].numProduct = numProduct;
                    }


                    totalnumcat += numCategory;
                    numCategory = 0;
                    SetColor(12);
                    printf("\n\n-------------------------------------------------------Done-------------------------------------------------------");
                    SetColor(15);
                }

                else if (x == 2)
                {
                    if(totalnumcat==0)
                    {
                        SetColor(12);
                        printf("\n Sorry No Category Existing to add product, Please Add Category First.");
                        SetColor(15);
                    }else
                    {
                        int index = 0; //start index from 0
                        printf("\n => Enter index of the category you would like to add \n\n   (Started from 0, 0 => first Category): ");
                        scanf("%d", &index);

                        if (index >=0 && index < totalnumcat)
                        {
                            int numProduct = 0;
                            printf("\n => Enter number of new products: ");
                            scanf("%d", &numProduct);

                            Cat[index].prod = realloc(Cat[index].prod,(Cat[index].numProduct + numProduct) * sizeof(Product));


                            for (int j = Cat[index].numProduct; j < Cat[index].numProduct+numProduct; j++)
                            {

                                printf("\n       Product %d For %s\n",j+1,Cat[index].CategoryName);
                                printf("\n Enter Product Name For %s:  ",Cat[index].CategoryName);
                                scanf("%s",Cat[index].prod[j].ProductName);
                                printf("\n Enter Product Price For %s: ",Cat[index].CategoryName);
                                scanf("%d",&Cat[index].prod[j].ProductPrice);

                                while(Cat[index].prod[j].ProductPrice <= 0)
                                {
                                    SetColor(12);
                                    printf("\n price invalid. Please Enter Positive Value.\n");
                                    SetColor(15);
                                    printf("\n Enter Product Price For %s: ",Cat[index].CategoryName);
                                    scanf("%d",&Cat[index].prod[j].ProductPrice);
                                }


                                printf("\n Enter Product Quantity For %s:  ",Cat[index].CategoryName);
                                scanf("%d",&Cat[index].prod[j].ProductQuantity);

                                while(Cat[index].prod[j].ProductQuantity <= 0)
                                {
                                    SetColor(12);
                                    printf("\n Quantity invalid. Please Enter Positive Value.\n");
                                    SetColor(15);
                                    printf("\n Enter Product Quantity For %s:  ",Cat[index].CategoryName);
                                    scanf("%d",&Cat[index].prod[j].ProductQuantity);
                                }



                                for(int k=0; k<j; k++)
                                {
                                    if(strcmp(Cat[index].prod[j].ProductName, Cat[index].prod[k].ProductName) == 0)
                                    {
                                        SetColor(12);
                                        printf("\n\n  Sorry, this product already exists in the category.\n");
                                        SetColor(15);
                                        j--; //to enter another name
                                    }
                                }

                            }


                           Cat[index].numProduct=Cat[index].numProduct+numProduct;
                        }
                        else
                        {
                            printf(" \n Index not correct.\n");
                        }
                        SetColor(12);
                        printf("\n\n-------------------------------------------------------Done-------------------------------------------------------");
                        SetColor(15);
                    }

                }


                getch();
                break;

            case 2:
                system("cls");
                DisplayCategoriesAndProducts(Cat, totalnumcat);
                getch();
                break;

            case 3:
                system("cls");
                DisplayCategoriesAndProducts(Cat, totalnumcat);
                MoveProduct(Cat ,totalnumcat);
                getch();
                break;


            case 4:
                system("cls");
                DisplayCategoriesAndProducts(Cat, totalnumcat);
                Order(Cat,totalnumcat);
                getch();
                break;

            case 5:
                system("cls");
                DisplayCategoriesAndProducts(Cat, totalnumcat);
                RemoveProduct(Cat,totalnumcat);
                getch();
                break;
            case 6:

                for(int i=0; i<totalnumcat;i++)
                {
                    free(Cat[i].prod);

                }
                free(Cat);
                printf("bye!\n");

                return 0;
            }
        }
    }

    return 0;
}


#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <algorithm>

#define EPSILON 0.0001f

struct Coords
{
    int x, y;

    bool operator==(const Coords &other) const
    {
        return x == other.x and y == other.y;
    }
};

struct Segment
{
    Coords p1, p2;
};

struct Triangle
{
    Coords p1, p2, p3;
    bool complet = false;
};

struct Polygon
{
    std::vector<Coords> points;
};

struct Circle
{
    Coords center;
    int radius;
};

struct Application
{
    int width, height;
    Coords focus{100, 100};

    std::vector<Coords> points;
    std::vector<Triangle> triangles;
    std::vector<Polygon> polygones;
    std::vector<Circle> circles;

    bool show_delaunay = true;
    bool show_voronoi = true;
    bool show_circum = true;
};

struct Color
{
    float r, g, b, a;
};

bool compareCoords(Coords point1, Coords point2)
{
    if (point1.y == point2.y)
        return point1.x < point2.x;
    return point1.y < point2.y;
}

bool compareAngles(const Coords &center, const Coords &p1, const Coords &p2)
{
    float angle1 = atan2(p1.y - center.y, p1.x - center.x);
    float angle2 = atan2(p2.y - center.y, p2.x - center.x);
    return angle1 < angle2;
}

void sortPointsByAngle(const Coords &center, std::vector<Coords> &points)
{
    std::sort(points.begin(), points.end(), [&](const Coords &p1, const Coords &p2)
              { return compareAngles(center, p1, p2); });
}

void drawPoints(SDL_Renderer *renderer, const std::vector<Coords> &points, Color color)
{
    for (std::size_t i = 0; i < points.size(); i++)
    {
        filledCircleRGBA(renderer, points[i].x, points[i].y, 3, color.r, color.g, color.b, color.a);
    }
}

void drawSegments(SDL_Renderer *renderer, const std::vector<Segment> &segments, Color color)
{
    for (std::size_t i = 0; i < segments.size(); i++)
    {
        lineRGBA(
            renderer,
            segments[i].p1.x, segments[i].p1.y,
            segments[i].p2.x, segments[i].p2.y,
            color.r, color.g, color.b, color.a);
    }
}

void drawTriangles(SDL_Renderer *renderer, const std::vector<Triangle> &triangles, Color color)
{
    for (std::size_t i = 0; i < triangles.size(); i++)
    {
        const Triangle &t = triangles[i];
        trigonRGBA(
            renderer,
            t.p1.x, t.p1.y,
            t.p2.x, t.p2.y,
            t.p3.x, t.p3.y,
            color.r, color.g, color.b, color.a);
    }
}

void drawPolygon(SDL_Renderer *renderer, const std::vector<Polygon> &polygones)
{
    for (std::size_t i = 0; i < polygones.size(); i++)
    {
        int r, g, b;

        // get rgb color unique based on index
        r = (i * 119) % 255;
        g = (i * 7) % 255;
        b = (i * 13) % 255;

        const Polygon &p = polygones[i];

        std::vector<Sint16> vx;
        std::vector<Sint16> vy;

        for (std::size_t j = 0; j < p.points.size(); j++)
        {
            vx.push_back(p.points[j].x);
            vy.push_back(p.points[j].y);
        }

        filledPolygonRGBA(renderer, vx.data(), vy.data(), vx.size(), r, g, b, SDL_ALPHA_OPAQUE);
    }
}

void drawCircles(SDL_Renderer *renderer, const std::vector<Circle> &circles, Color color)
{
    for (std::size_t i = 0; i < circles.size(); i++)
    {
        const Circle &c = circles[i];

        // draw circle of circum of triangle

        // circleRGBA(
        //     renderer,
        //     c.center.x, c.center.y,
        //     c.radius,
        //     color.r, color.g, color.b, color.a);

        // draw center of the circle
        filledCircleRGBA(renderer, c.center.x, c.center.y, 3, 255, 0, 0, 255);
    }
}

void draw(SDL_Renderer *renderer, const Application &app)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */
    int width, height;
    SDL_GetRendererOutputSize(renderer, &width, &height);

    Color color_delaunay_points = {240, 240, 23, SDL_ALPHA_OPAQUE};
    Color color_delaunay_segments = {240, 240, 20, SDL_ALPHA_OPAQUE};
    Color color_delaunay_triangles = {0, 240, 160, SDL_ALPHA_OPAQUE};

    if (app.show_voronoi)
        drawPolygon(renderer, app.polygones);
    if (app.show_circum)
        drawCircles(renderer, app.circles, color_delaunay_segments);
    if (app.show_delaunay)
    {
        drawTriangles(renderer, app.triangles, color_delaunay_triangles);
        drawPoints(renderer, app.points, color_delaunay_points);
    }
}

/*
   Détermine si un point se trouve dans un cercle définit par trois points
   Retourne, par les paramètres, le centre et le rayon
*/
bool CircumCircle(
    float pX, float pY,
    float x1, float y1, float x2, float y2, float x3, float y3,
    float *xc, float *yc, float *rsqr)
{
    float m1, m2, mx1, mx2, my1, my2;
    float dx, dy, drsqr;
    float fabsy1y2 = fabs(y1 - y2);
    float fabsy2y3 = fabs(y2 - y3);

    /* Check for coincident points */
    if (fabsy1y2 < EPSILON && fabsy2y3 < EPSILON)
        return (false);

    if (fabsy1y2 < EPSILON)
    {
        m2 = -(x3 - x2) / (y3 - y2);
        mx2 = (x2 + x3) / 2.0;
        my2 = (y2 + y3) / 2.0;
        *xc = (x2 + x1) / 2.0;
        *yc = m2 * (*xc - mx2) + my2;
    }
    else if (fabsy2y3 < EPSILON)
    {
        m1 = -(x2 - x1) / (y2 - y1);
        mx1 = (x1 + x2) / 2.0;
        my1 = (y1 + y2) / 2.0;
        *xc = (x3 + x2) / 2.0;
        *yc = m1 * (*xc - mx1) + my1;
    }
    else
    {
        m1 = -(x2 - x1) / (y2 - y1);
        m2 = -(x3 - x2) / (y3 - y2);
        mx1 = (x1 + x2) / 2.0;
        mx2 = (x2 + x3) / 2.0;
        my1 = (y1 + y2) / 2.0;
        my2 = (y2 + y3) / 2.0;
        *xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        if (fabsy1y2 > fabsy2y3)
        {
            *yc = m1 * (*xc - mx1) + my1;
        }
        else
        {
            *yc = m2 * (*xc - mx2) + my2;
        }
    }

    dx = x2 - *xc;
    dy = y2 - *yc;
    *rsqr = dx * dx + dy * dy;

    dx = pX - *xc;
    dy = pY - *yc;
    drsqr = dx * dx + dy * dy;

    return ((drsqr - *rsqr) <= EPSILON ? true : false);
}

void construitVoronoi(Application &app)
{
    // Trier les points selon x
    std::sort(app.points.begin(), app.points.end(), compareCoords);

    // Vider la liste existante de triangles
    app.triangles.clear();
    app.circles.clear();
    app.polygones.clear();

    // Créer un trés grand triangle (-1000, -1000); (500, 3000); (1500, -1000)
    Triangle bigTriangle = {{-1000, -1000}, {500, 3000}, {1500, -1000}};

    // Le rajouter à la liste de triangles déjà créés
    app.triangles.push_back(bigTriangle);

    // Pour chaque point P du repère:
    for (size_t i = 0; i < app.points.size(); i++)
    {
        // Créer une liste de segments LS
        std::vector<Segment> listeSegments;

        for (size_t j = 0; j < app.triangles.size(); j++)
        {
            //  Tester si le cercle circonscrit contient le point P
            float xc, yc, rsqr;
            bool isCircum = CircumCircle(
                app.points[i].x,
                app.points[i].y,
                app.triangles[j].p1.x,
                app.triangles[j].p1.y,
                app.triangles[j].p2.x,
                app.triangles[j].p2.y,
                app.triangles[j].p3.x,
                app.triangles[j].p3.y,
                &xc,
                &yc,
                &rsqr);

            if (isCircum)
            {
                // draw circle of circum
                Circle circle = {{(int)xc, (int)yc}, (int)rsqr};
                app.circles.push_back(circle);

                // Récupérer les différents segments de ce triangles dans LS
                Segment seg_1 = {{app.triangles[j].p1.x, app.triangles[j].p1.y}, {app.triangles[j].p2.x, app.triangles[j].p2.y}};
                Segment seg_2 = {{app.triangles[j].p2.x, app.triangles[j].p2.y}, {app.triangles[j].p3.x, app.triangles[j].p3.y}};
                Segment seg_3 = {{app.triangles[j].p3.x, app.triangles[j].p3.y}, {app.triangles[j].p1.x, app.triangles[j].p1.y}};

                listeSegments.push_back(seg_1);
                listeSegments.push_back(seg_2);
                listeSegments.push_back(seg_3);

                // Enlever le triangke T de la liste
                app.triangles.erase(app.triangles.begin() + j);
                j--;
            }
        }

        // Pour chaque segment S de la liste LS faire
        for (size_t j = 0; j < listeSegments.size(); j++)
        {
            for (size_t k = 0; k < listeSegments.size(); k++)
            {
                if (k == j)
                    break;

                // Si un segment est un doublon d’un autre alors
                if ((listeSegments[j].p1 == listeSegments[k].p2) && (listeSegments[j].p2 == listeSegments[k].p1))
                {
                    // Les virers
                    listeSegments.erase(listeSegments.begin() + k);
                    k--;
                    j--;
                    listeSegments.erase(listeSegments.begin() + j);
                }
            }
        }

        // Pour chaque segment S de la liste LS faire
        for (size_t j = 0; j < listeSegments.size(); j++)
        {
            // Créer un nouveau triangle composé du segment S et du point P;
            Triangle triangle = {
                listeSegments[j].p1,
                listeSegments[j].p2,
                {app.points[i].x,
                 app.points[i].y}};

            app.triangles.push_back(triangle);
        }
    }

    // Créer une liste de polygones
    std::vector<Polygon> polygones;

    for (size_t i = 0; i < app.points.size(); i++)
    {
        // Créer un polygone
        Polygon polygone;

        for (size_t j = 0; j < app.triangles.size(); j++)
        {
            // Si le triangle contient le point P (adjacent)
            if (app.triangles[j].p1 == app.points[i] || app.triangles[j].p2 == app.points[i] || app.triangles[j].p3 == app.points[i])
            {
                // Récupérer le centre du cercle circonscrit
                float xc, yc, rsqr;
                CircumCircle(app.triangles[j].p1.x, app.triangles[j].p1.y, app.triangles[j].p1.x, app.triangles[j].p1.y, app.triangles[j].p2.x, app.triangles[j].p2.y, app.triangles[j].p3.x, app.triangles[j].p3.y,
                             &xc, &yc, &rsqr);

                // Ajouter le centre du cercle circonscrit au polygone
                polygone.points.push_back({(int)xc, (int)yc});

                // Trier les points du polygone par angle croissant
                sortPointsByAngle(app.points[i], polygone.points);

                // Ajouter le polygone à la liste de polygones pour le dessiner
                app.polygones.push_back(polygone);
            }
        }
    }
}

bool handleEvent(Application &app)
{
    /* Remplissez cette fonction pour gérer les inputs utilisateurs */
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
                return false;

            if (e.key.keysym.sym == SDLK_d) // On D, toggle app.delaunay
            {
                app.show_delaunay = !app.show_delaunay;
            }
            else if (e.key.keysym.sym == SDLK_c) // On C, toggle app.circum
            {
                app.show_circum = !app.show_circum;
            }
            else if (e.key.keysym.sym == SDLK_v) // On V, toggle app.polygones
            {
                app.show_voronoi = !app.show_voronoi;
            }
        }
        else if (e.type == SDL_QUIT)
            return false;
        else if (e.type == SDL_WINDOWEVENT_RESIZED)
        {
            app.width = e.window.data1;
            app.height = e.window.data1;
        }
        else if (e.type == SDL_MOUSEBUTTONUP)
        {
            if (e.button.button == SDL_BUTTON_RIGHT)
            {
                app.focus.x = e.button.x;
                app.focus.y = e.button.y;
                app.points.clear();
                app.triangles.clear();
                app.polygones.clear();
                app.circles.clear();
            }
            else if (e.button.button == SDL_BUTTON_LEFT)
            {
                app.focus.y = 0;
                app.points.push_back(Coords{e.button.x, e.button.y});
                construitVoronoi(app);
            }
        }
    }
    return true;
}

int main(int argc, char **argv)
{
    SDL_Window *gWindow;
    SDL_Renderer *renderer;
    Application app{720, 720, Coords{0, 0}};
    bool is_running = true;

    // Creation de la fenetre
    gWindow = init("The IMAC Voronoi !", 720, 720);

    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

    /*  GAME LOOP  */
    while (true)
    {
        // INPUTS
        is_running = handleEvent(app);
        if (!is_running)
            break;

        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // DESSIN
        draw(renderer, app);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000 / 30);
    }

    // Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}

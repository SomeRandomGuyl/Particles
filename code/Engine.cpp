#include "Engine.h"

Engine::Engine()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(resolution.x, resolution.y), "Particles!", Style::Fullscreen);
}

Engine::run()
{
    sf::Clock clock;
    sf::Time dt = clock.getElapsedTime();

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_window.isOpen())
    {
        sf::Clock::restart();
        sf::Time dt = sf::seconds(0.1f);

        input();
        update();
        draw();
    }
}

Engine::input()
{
    vector<Vector2i> mouseClicks;
    Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_Window.close();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                mouseClicks.push_back(Vector2i(event.mouseButton.x))
                for (int i = 0; i < 5; i++)
                {
                    int nPoints = rand()%25 + 25;
                    mouseClicks.push_back(Particle(m_Window, nPoints, mouseClicks[i]))
                }
            }
        }
    }
}

Engine::update(float dtAsSeconds)
{
    vector<int>::iterator i = m_particles.begin();

    for(i != m_particles.end())
    {
        if (getTTL() > 0.0)
        {
            update(dt);
            ++i
        }
        else
        {
            i = m_particles.erase(i);
        }
    }
}

Engine::draw()
{
    
}
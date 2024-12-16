#include "Engine.h"

Engine::Engine()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(resolution.x, resolution.y), "Particles!", Style::Fullscreen);
}

void Engine::run()
{
    sf::Clock clock;
    sf::Time dt = clock.getElapsedTime();

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen())
    {
        dt = clock.restart();
        float seconds = dt.asSeconds();
        

        input();
        update(seconds);
        draw();
    }
}

void Engine::input()
{
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
                for (int i = 0; i < 5; i++)
                {
                    Vector2i mouseClicks = {event.mouseButton.x, event.mouseButton.y};
                    int nPoints = rand()%25 + 25;
                    m_particles.push_back(Particle(m_Window, nPoints, mouseClicks));
                }
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    vector<Particle>::iterator i = m_particles.begin();

    while(i != m_particles.end())
    //for (int i = 0; i < m_particles.size();)
    {
        if (i->getTTL() > 0.0)
        {
            i->update(dtAsSeconds);
            ++i;
        }
        else
        {
            i = m_particles.erase(i);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    for(int i = 0; i < m_particles.size(); i++)
    {
        m_Window.draw(m_particles[i]);
    }

    m_Window.display();
}

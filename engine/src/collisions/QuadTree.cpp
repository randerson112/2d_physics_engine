// Implementation of QuadTree class

#include "collisions/QuadTree.hpp"

namespace phys
{
    // === Public ===

    QuadTree::QuadTree(const Vector2& min, const Vector2& max)
        : m_root(min, max)
    {
    }

    void QuadTree::insert(PhysicsBody* body)
    {
        insertNode(&m_root, body, 0);
    }

    void QuadTree::clear()
    {
        clearNode(&m_root);
    }

    // === Private ===
    
    void QuadTree::insertNode(QuadTreeNode* node, PhysicsBody* body, int depth)
    {
        const AABB& bodyAABB = body->getCollider()->getAABB();

        // If body is not intersecting node return early
        if (!bodyAABB.intersects(node->bounds))
            return;

        // If node has space and has no children or at max depth insert here for now
        if ((node->bodies.size() < m_maxBodiesPerNode && !node->hasChildren) || depth >= m_maxDepth)
        {
            node->bodies.push_back(body);
            return;
        }

        // If node is full and has no children, subdivide and move existing bodies
        if (node->bodies.size() >= m_maxBodiesPerNode && !node->hasChildren)
        {
            subdivideNode(node);

            std::vector<PhysicsBody*> keptBodies;
            keptBodies.reserve(node->bodies.size());

            for (const auto& existingBody : node->bodies)
            {
                const AABB& existingBodyAABB = existingBody->getCollider()->getAABB();
                bool inserted = false;

                for (auto& child : node->childNodes)
                {
                    if (child->bounds.contains(existingBodyAABB))
                    {
                        insertNode(child, existingBody, depth + 1);
                        inserted = true;
                        break;
                    }
                }

                if (!inserted)
                    keptBodies.push_back(existingBody);
            }

            node->bodies = std::move(keptBodies);
        }

        // Now try to insert body into one of the children
        bool inserted = false;
        for (auto& child : node->childNodes)
        {
            if (child->bounds.contains(bodyAABB))
            {
                insertNode(child, body, depth + 1);
                inserted = true;
                break;
            }
        }

        // Keep in parent if it does not fit in a child
        if (!inserted)
            node->bodies.push_back(body);
    }

    void QuadTree::subdivideNode(QuadTreeNode* node)
    {
        // If node is already subdivided, exit
        if (node->hasChildren)
            return;

        // Get bounds of node and center
        const AABB bounds = node->bounds;
        const Vector2 center = {
            (bounds.min.x + bounds.max.x) * 0.5f,
            (bounds.min.y + bounds.max.y) * 0.5f
        };

        // Create child nodes in 4 quadrants of parent node
        node->childNodes[0] = new QuadTreeNode({bounds.min.x, center.y}, {center.x, bounds.max.y});
        node->childNodes[1] = new QuadTreeNode(center, bounds.max);
        node->childNodes[2] = new QuadTreeNode(bounds.min, center);
        node->childNodes[3] = new QuadTreeNode({center.x, bounds.min.y}, {bounds.max.x, center.y});

        node->hasChildren = true;
    }

    void QuadTree::clearNode(QuadTreeNode* node)
    {
        // Clear bodies in node
        node->bodies.clear();

        // Clear bodies in children and delete children
        for (int i = 0; i < 4; i++)
        {
            if (node->childNodes[i])
            {
                clearNode(node->childNodes[i]);
                delete node->childNodes[i];
                node->childNodes[i] = nullptr; 
            }
        }
        node->hasChildren = false;
    }
}
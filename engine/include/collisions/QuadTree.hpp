#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include "collisions/AABB.hpp"
#include "physics/PhysicsBody.hpp"
#include <vector>
#include <array>

namespace phys
{

    struct QuadTreeNode
    {
        // Bounds for node in world space
        AABB bounds;

        // Physics bodies contained in this node
        std::vector<PhysicsBody*> bodies;

        // Child nodes of this node
        std::array<QuadTreeNode*, 4> childNodes;

        // Flag to check if this node has children
        bool hasChildren;

        // Constructor sets bounds of node and no children by default
        QuadTreeNode(const Vector2& min, const Vector2& max)
            : bounds(min, max)
        {
            childNodes.fill(nullptr);
            hasChildren = false;
        }

        // Destructor to delete children
        ~QuadTreeNode()
        {
            for (int i = 0; i < 4; i++)
            {
                delete childNodes[i];
            }
        }
    };

    class QuadTree
    {
    private:
        // Root node of the tree
        QuadTreeNode m_root;

        // Max amount of bodies per node before subdividing
        int m_maxBodiesPerNode = 5;

        // Max depth of subdivisions
        int m_maxDepth = 10;

        // Recursively inserts a physics body into a node, subdividing if needed
        void insertNode(QuadTreeNode* node, PhysicsBody* body, int depth);

        // Divides a node into 4 child nodes, moving bodies into children
        void subdivideNode(QuadTreeNode* node);

        // Recursively clears bodies in a node and and deletes children
        void clearNode(QuadTreeNode* node);

        // Recursively gathers all potentially colliding body pairs within a node and its children
        void gatherPairsInNode(QuadTreeNode* node, std::vector<std::pair<PhysicsBody*, PhysicsBody*>>& pairs);

        // Collects potential collision pairs between a single body and all bodies
        // within a node (and its children) whose bounds intersect the body’s AABB
        void gatherPairsBodyVsNode(PhysicsBody* body, QuadTreeNode* node, std::vector<std::pair<PhysicsBody*, PhysicsBody*>>& pairs);

    public:
        // Constructor sets the bounds of the tree
        QuadTree(const Vector2& dimensions);

        // Inserts a body into the tree
        void insert(PhysicsBody* body);

        // Gathers all potentially colliding body pairs in the entire tree
        void gatherPairs(std::vector<std::pair<PhysicsBody*, PhysicsBody*>>& pairs);

        // Clears the tree and all children
        void clear();
    };

}

#endif // QUADTREE_HPP

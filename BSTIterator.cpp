class BSTIterator {
    
    std::stack<TreeNode*> st;
public:
    BSTIterator(TreeNode* root) {
        goLeft(root);
    }
    
    void goLeft(TreeNode *root) {
        TreeNode *curr = root;
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
    }
    
    int next() {
        TreeNode *tp = st.top();
        st.pop();
        goLeft(tp->right);
        return tp->val;
    }
    
    bool hasNext() {
        return st.size();
    }
};

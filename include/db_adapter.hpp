/**
 * @file   db_adapter.hpp
 * @author  <devil@Funtoo>
 * @date   Mon Jul  8 09:25:54 2013
 * 
 * @brief  DB Adapter class, which will handle communication between secureindex service and database
 * 
 * 
 */

#ifndef __FOLLOWME_DB_ADAPTER_HPP__
#define __FLOOLWME_DB_ADAPTER_HPP__
#include "db_conn_pool.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "db_conn_pool.hpp"
#include "config.hpp"
#include <vector>
#include <utility>
#include <map>

namespace secureindex{
    
    class T_DOC;
    
    class DBAdapter :public boost::noncopyable
    {
    public:
        /** 
         * Constructor for DBAdapter class
         *
         * @param config 
         *
         * @return 
         */
        DBAdapter( boost::shared_ptr<Config> config );
        
        
        std::vector<std::pair<std::string, std::string> >  get_all_remote_file_list();
        
        /** 
         * Add a document type data into database
         *
         * @param doc_id  is document id, which was generated by document content with a SHA1 hash
         * @param doc_name  is document file name
         * @param index   is doucment index , the same with secureindex index
         * @param o_index is another doucment index, which is for occurrence search algorithm
         * @param encrypt_stream  is encrypted from document data with AES hash
         */
        
        void add_document( std::string const & doc_id, 
                           std::string const & doc_name,
                           std::string const & index,
                           std::string const & o_index,
                           std::string const & encrypt_stream);
        
        /** 
         * Delete document item from database
         *
         * @param doc_id is document id
         */
        void delete_document_by_id(std::string const & doc_id);
        
        /** 
         * Delete document item from database
         *
         * @param doc_name is the document name
         */
        void delete_document_by_name(std::string const & doc_name);

        /** 
         * Update document item in database with data
         *
         * @param old_doc_id is the document id from which the doc will be updated.
         * @param new_doc_id is new generated document id
         * @param new_doc_name is the document name
         * @param new_doc_index is the document index
         * @param new_doc_o_index is the document index for occurrence search
         * @param stream 
         */
        void update_document_by_id( std::string const & old_doc_id,
                                    std::string const & new_doc_id,
                                    std::string const & new_doc_name,
                                    std::string const & new_doc_index,
                                    std::string const & new_doc_o_index,
                                    std::string const & stream);
        
        /** 
         * Update document by name in database
         *
         * @param old_doc_name 
         * @param new_doc_name 
         * @param new_doc_id 
         * @param new_doc_index 
         * @param new_doc_o_index 
         * @param stream 
         */
        void update_document_by_name ( std::string const & old_doc_name,
                                       std::string const & new_doc_name,
                                       std::string const & new_doc_id,
                                       std::string const & new_doc_index,
                                       std::string const & new_doc_o_index,
                                       std::string const & stream);
        
        /** 
         * Get document index by doc_id, from the database
         *
         * @param doc_id 
         *
         * @return 
         */
        std::string get_document_index_by_id(std::string const & doc_id);
        
        std::string get_document_index_by_name(std::string const & doc_name);
        
        std::string get_document_oindex_by_name(std::string const & doc_name);
                
        std::string get_document_by_name(std::string const & doc_name);
        
    private:
        
        /// poolptr is the share_point for mysql connector.
        boost::shared_ptr<MysqlConnPool> poolptr;
        
        /// config_ should be singleton instance, which is a global settings from a config file
        boost::shared_ptr<Config> config_;
                
        bool is_exist_doc_id(std::string const & doc_id);
        
        bool is_exist_doc_name( std::string const & name);
        
    };
}
#endif
